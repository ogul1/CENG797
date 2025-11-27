#include "MstClustering.h"
#include <cmath>
#include <limits>
#include <algorithm>
#include <sstream>
#include <inet/mobility/contract/IMobility.h>
#include <inet/common/ModuleAccess.h>
using namespace inet;
using namespace std;

Define_Module(MstClustering);

static const char *CLUSTER_COLORS[] = {
    "red","blue","green","orange","purple","yellow","cyan","magenta","brown","pink","gray","darkblue","darkgreen"
};
static const int NUM_COLORS = sizeof(CLUSTER_COLORS)/sizeof(CLUSTER_COLORS[0]);

void MstClustering::initialize() {
    period = par("period").doubleValue();
    commRange = par("commRange").doubleValue();

    timer = new cMessage("mstTimer");
    scheduleAt(simTime() + 0.2, timer);
}

void MstClustering::handleMessage(cMessage *msg) {
    if (msg != timer) {
        delete msg;
        return;
    }

    cModule *top = getSimulation()->getSystemModule();
    vector<cModule*> hostModules;
    for (cModule::SubmoduleIterator it(top); !it.end(); ++it) {
        cModule *m = *it;

        if (string(m->getName()).rfind("host", 0) == 0) {
            hostModules.push_back(m);
        }
    }

    sort(hostModules.begin(), hostModules.end(), [](cModule* a, cModule* b){ return string(a->getFullPath()) < string(b->getFullPath()); });

    vector<pair<double,double>> positions;
    positions.reserve(hostModules.size());

    for (auto *h : hostModules) {
        cModule *mobSub = h->getSubmodule("mobility");
        IMobility *mob = check_and_cast<IMobility*>(mobSub);
        Coord c = mob->getCurrentPosition();
        positions.push_back({c.x, c.y});
    }

    auto clusters = computeClusters(positions);

    for (int i = 0; i < hostModules.size(); ++i) {
        int cId = clusters[i];
        const char *color = CLUSTER_COLORS[cId % NUM_COLORS];
        cModule *mobSub = hostModules[i]->getSubmodule("mobility");
        IMobility *mob = check_and_cast<IMobility*>(mobSub);
        Coord pos = mob->getCurrentPosition();
        char buf[64];
        snprintf(buf, sizeof(buf), "Cluster %d | (%.1f, %.1f)", cId, pos.x, pos.y);

        cDisplayString &ds = hostModules[i]->getDisplayString();
        ds.setTagArg("b", 2, "oval");
        ds.setTagArg("b", 0, "50");
        ds.setTagArg("b", 1, "50");
        ds.setTagArg("b", 3, color);
        ds.setTagArg("t", 0, buf);
    }

    scheduleAt(simTime() + period, timer);
}

void MstClustering::finish()
{
    cancelAndDelete(timer);
    timer = nullptr;
}

vector<int> MstClustering::computeClusters(const vector<pair<double, double>>& pos) {
    int n = pos.size();
    if (n == 0) {
        return {};
    }

    vector<vector<double>> dist(n, vector<double>(n, 0.0));
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            double dx = pos[i].first - pos[j].first;
            double dy = pos[i].second - pos[j].second;
            double d = sqrt(dx * dx + dy * dy);
            dist[i][j] = dist[j][i] = d;
        }
    }
    vector<bool> inMST(n, false);
    vector<int> parent(n, -1);

    using Edge = tuple<double, int, int>;
    priority_queue<Edge, vector<Edge>, greater<Edge>> pq;

    inMST[0] = true;
    for (int v = 1; v < n; v++) {
        pq.push({dist[0][v], 0, v});
    }

    int added = 1;
    while (added < n && !pq.empty()) {
        auto [w, u, v] = pq.top();
        pq.pop();

        if (inMST[v]) {
            continue;
        }

        inMST[v] = true;
        parent[v] = u;
        added++;

        for (int x = 0; x < n; x++) {
            if (!inMST[x]) {
                pq.push({dist[v][x], v, x});
            }
        }
    }

    vector<vector<int>> adj(n);
    for (int v = 1; v < n; v++) {
        int p = parent[v];
        if (p >= 0) {
            adj[v].push_back(p);
            adj[p].push_back(v);
        }
    }

    for (int i = 0; i < n; i++) {
        for (auto it = adj[i].begin(); it != adj[i].end();) {
            int j = *it;
            if (dist[i][j] > commRange) {
                it = adj[i].erase(it);
                auto& L = adj[j];
                L.erase(remove(L.begin(), L.end(), (int)i), L.end());
            } else {
                ++it;
            }
        }
    }

    vector<int> cluster(n, -1);
    int cid = 0;

    for (int i = 0; i < n; i++) {
        if (cluster[i] != -1) {
            continue;
        }

        vector<int> st = {i};
        cluster[i] = cid;

        while (!st.empty()) {
            int u = st.back();
            st.pop_back();
            for (int v : adj[u]) {
                if (cluster[v] == -1) {
                    cluster[v] = cid;
                    st.push_back(v);
                }
            }
        }
        cid++;
    }

    return cluster;
}
