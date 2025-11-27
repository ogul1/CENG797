#ifndef MSTCLUSTERING_H_
#define MSTCLUSTERING_H_

#include <omnetpp.h>
#include <vector>
#include <string>

using namespace omnetpp;

class MstClustering : public cSimpleModule
{
  private:
    cMessage *timer = nullptr;
    double period;
    double commRange;
  protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
    virtual void finish() override;

    // helpers
    std::vector<std::pair<double,double>> collectPositions();
    std::vector<int> computeClusters(const std::vector<std::pair<double,double>>& pos);
    std::pair<double,double> parsePositionFromDisplayString(cModule *mod);
    std::string shortModuleName(cModule *mod);
};

#endif /* MSTCLUSTERING_H_ */
