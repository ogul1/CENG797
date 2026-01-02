//
// Generated file, do not edit! Created by opp_msgtool 6.2 from MstClusteringPacket.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wshadow"
#  pragma clang diagnostic ignored "-Wconversion"
#  pragma clang diagnostic ignored "-Wunused-parameter"
#  pragma clang diagnostic ignored "-Wc++98-compat"
#  pragma clang diagnostic ignored "-Wunreachable-code-break"
#  pragma clang diagnostic ignored "-Wold-style-cast"
#elif defined(__GNUC__)
#  pragma GCC diagnostic ignored "-Wshadow"
#  pragma GCC diagnostic ignored "-Wconversion"
#  pragma GCC diagnostic ignored "-Wunused-parameter"
#  pragma GCC diagnostic ignored "-Wold-style-cast"
#  pragma GCC diagnostic ignored "-Wsuggest-attribute=noreturn"
#  pragma GCC diagnostic ignored "-Wfloat-conversion"
#endif

#include <iostream>
#include <sstream>
#include <memory>
#include <type_traits>
#include "MstClusteringPacket_m.h"

namespace omnetpp {

// Template pack/unpack rules. They are declared *after* a1l type-specific pack functions for multiple reasons.
// They are in the omnetpp namespace, to allow them to be found by argument-dependent lookup via the cCommBuffer argument

// Packing/unpacking an std::vector
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::vector<T,A>& v)
{
    int n = v.size();
    doParsimPacking(buffer, n);
    for (int i = 0; i < n; i++)
        doParsimPacking(buffer, v[i]);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::vector<T,A>& v)
{
    int n;
    doParsimUnpacking(buffer, n);
    v.resize(n);
    for (int i = 0; i < n; i++)
        doParsimUnpacking(buffer, v[i]);
}

// Packing/unpacking an std::list
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::list<T,A>& l)
{
    doParsimPacking(buffer, (int)l.size());
    for (typename std::list<T,A>::const_iterator it = l.begin(); it != l.end(); ++it)
        doParsimPacking(buffer, (T&)*it);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::list<T,A>& l)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        l.push_back(T());
        doParsimUnpacking(buffer, l.back());
    }
}

// Packing/unpacking an std::set
template<typename T, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::set<T,Tr,A>& s)
{
    doParsimPacking(buffer, (int)s.size());
    for (typename std::set<T,Tr,A>::const_iterator it = s.begin(); it != s.end(); ++it)
        doParsimPacking(buffer, *it);
}

template<typename T, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::set<T,Tr,A>& s)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        T x;
        doParsimUnpacking(buffer, x);
        s.insert(x);
    }
}

// Packing/unpacking an std::map
template<typename K, typename V, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::map<K,V,Tr,A>& m)
{
    doParsimPacking(buffer, (int)m.size());
    for (typename std::map<K,V,Tr,A>::const_iterator it = m.begin(); it != m.end(); ++it) {
        doParsimPacking(buffer, it->first);
        doParsimPacking(buffer, it->second);
    }
}

template<typename K, typename V, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::map<K,V,Tr,A>& m)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        K k; V v;
        doParsimUnpacking(buffer, k);
        doParsimUnpacking(buffer, v);
        m[k] = v;
    }
}

// Default pack/unpack function for arrays
template<typename T>
void doParsimArrayPacking(omnetpp::cCommBuffer *b, const T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimPacking(b, t[i]);
}

template<typename T>
void doParsimArrayUnpacking(omnetpp::cCommBuffer *b, T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimUnpacking(b, t[i]);
}

// Default rule to prevent compiler from choosing base class' doParsimPacking() function
template<typename T>
void doParsimPacking(omnetpp::cCommBuffer *, const T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimPacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

template<typename T>
void doParsimUnpacking(omnetpp::cCommBuffer *, T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimUnpacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

}  // namespace omnetpp

namespace mstclustering {

Register_Enum(mstclustering::MstClusteringMsgType, (mstclustering::MstClusteringMsgType::MSG_HELLO, mstclustering::MstClusteringMsgType::MSG_TOPOLOGY_UPDATE, mstclustering::MstClusteringMsgType::MSG_CLUSTER_JOIN, mstclustering::MstClusteringMsgType::MSG_CLUSTER_HEAD, mstclustering::MstClusteringMsgType::MSG_CLUSTER_ACK, mstclustering::MstClusteringMsgType::MSG_CLUSTER_LEAVE, mstclustering::MstClusteringMsgType::MSG_EDGE_INFO));

Register_Enum(mstclustering::NodeRole, (mstclustering::NodeRole::ROLE_UNDECIDED, mstclustering::NodeRole::ROLE_CLUSTER_MEMBER, mstclustering::NodeRole::ROLE_CLUSTER_HEAD, mstclustering::NodeRole::ROLE_GATEWAY));

Register_Class(HelloPacket)

HelloPacket::HelloPacket() : ::inet::FieldsChunk()
{
}

HelloPacket::HelloPacket(const HelloPacket& other) : ::inet::FieldsChunk(other)
{
    copy(other);
}

HelloPacket::~HelloPacket()
{
}

HelloPacket& HelloPacket::operator=(const HelloPacket& other)
{
    if (this == &other) return *this;
    ::inet::FieldsChunk::operator=(other);
    copy(other);
    return *this;
}

void HelloPacket::copy(const HelloPacket& other)
{
    this->nodeId = other.nodeId;
    this->posX = other.posX;
    this->posY = other.posY;
    this->posZ = other.posZ;
    this->energy = other.energy;
    this->clusterId = other.clusterId;
    this->clusterHeadId = other.clusterHeadId;
    this->nodeRole = other.nodeRole;
    this->sequenceNumber = other.sequenceNumber;
    this->numNeighbors = other.numNeighbors;
    this->timestamp = other.timestamp;
}

void HelloPacket::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::FieldsChunk::parsimPack(b);
    doParsimPacking(b,this->nodeId);
    doParsimPacking(b,this->posX);
    doParsimPacking(b,this->posY);
    doParsimPacking(b,this->posZ);
    doParsimPacking(b,this->energy);
    doParsimPacking(b,this->clusterId);
    doParsimPacking(b,this->clusterHeadId);
    doParsimPacking(b,this->nodeRole);
    doParsimPacking(b,this->sequenceNumber);
    doParsimPacking(b,this->numNeighbors);
    doParsimPacking(b,this->timestamp);
}

void HelloPacket::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::FieldsChunk::parsimUnpack(b);
    doParsimUnpacking(b,this->nodeId);
    doParsimUnpacking(b,this->posX);
    doParsimUnpacking(b,this->posY);
    doParsimUnpacking(b,this->posZ);
    doParsimUnpacking(b,this->energy);
    doParsimUnpacking(b,this->clusterId);
    doParsimUnpacking(b,this->clusterHeadId);
    doParsimUnpacking(b,this->nodeRole);
    doParsimUnpacking(b,this->sequenceNumber);
    doParsimUnpacking(b,this->numNeighbors);
    doParsimUnpacking(b,this->timestamp);
}

int HelloPacket::getNodeId() const
{
    return this->nodeId;
}

void HelloPacket::setNodeId(int nodeId)
{
    handleChange();
    this->nodeId = nodeId;
}

double HelloPacket::getPosX() const
{
    return this->posX;
}

void HelloPacket::setPosX(double posX)
{
    handleChange();
    this->posX = posX;
}

double HelloPacket::getPosY() const
{
    return this->posY;
}

void HelloPacket::setPosY(double posY)
{
    handleChange();
    this->posY = posY;
}

double HelloPacket::getPosZ() const
{
    return this->posZ;
}

void HelloPacket::setPosZ(double posZ)
{
    handleChange();
    this->posZ = posZ;
}

double HelloPacket::getEnergy() const
{
    return this->energy;
}

void HelloPacket::setEnergy(double energy)
{
    handleChange();
    this->energy = energy;
}

int HelloPacket::getClusterId() const
{
    return this->clusterId;
}

void HelloPacket::setClusterId(int clusterId)
{
    handleChange();
    this->clusterId = clusterId;
}

int HelloPacket::getClusterHeadId() const
{
    return this->clusterHeadId;
}

void HelloPacket::setClusterHeadId(int clusterHeadId)
{
    handleChange();
    this->clusterHeadId = clusterHeadId;
}

int HelloPacket::getNodeRole() const
{
    return this->nodeRole;
}

void HelloPacket::setNodeRole(int nodeRole)
{
    handleChange();
    this->nodeRole = nodeRole;
}

int HelloPacket::getSequenceNumber() const
{
    return this->sequenceNumber;
}

void HelloPacket::setSequenceNumber(int sequenceNumber)
{
    handleChange();
    this->sequenceNumber = sequenceNumber;
}

int HelloPacket::getNumNeighbors() const
{
    return this->numNeighbors;
}

void HelloPacket::setNumNeighbors(int numNeighbors)
{
    handleChange();
    this->numNeighbors = numNeighbors;
}

::omnetpp::simtime_t HelloPacket::getTimestamp() const
{
    return this->timestamp;
}

void HelloPacket::setTimestamp(::omnetpp::simtime_t timestamp)
{
    handleChange();
    this->timestamp = timestamp;
}

class HelloPacketDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_nodeId,
        FIELD_posX,
        FIELD_posY,
        FIELD_posZ,
        FIELD_energy,
        FIELD_clusterId,
        FIELD_clusterHeadId,
        FIELD_nodeRole,
        FIELD_sequenceNumber,
        FIELD_numNeighbors,
        FIELD_timestamp,
    };
  public:
    HelloPacketDescriptor();
    virtual ~HelloPacketDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyName) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyName) const override;
    virtual int getFieldArraySize(omnetpp::any_ptr object, int field) const override;
    virtual void setFieldArraySize(omnetpp::any_ptr object, int field, int size) const override;

    virtual const char *getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const override;
    virtual std::string getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const override;
    virtual omnetpp::cValue getFieldValue(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual omnetpp::any_ptr getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const override;
};

Register_ClassDescriptor(HelloPacketDescriptor)

HelloPacketDescriptor::HelloPacketDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(mstclustering::HelloPacket)), "inet::FieldsChunk")
{
    propertyNames = nullptr;
}

HelloPacketDescriptor::~HelloPacketDescriptor()
{
    delete[] propertyNames;
}

bool HelloPacketDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<HelloPacket *>(obj)!=nullptr;
}

const char **HelloPacketDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *HelloPacketDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int HelloPacketDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 11+base->getFieldCount() : 11;
}

unsigned int HelloPacketDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_nodeId
        FD_ISEDITABLE,    // FIELD_posX
        FD_ISEDITABLE,    // FIELD_posY
        FD_ISEDITABLE,    // FIELD_posZ
        FD_ISEDITABLE,    // FIELD_energy
        FD_ISEDITABLE,    // FIELD_clusterId
        FD_ISEDITABLE,    // FIELD_clusterHeadId
        FD_ISEDITABLE,    // FIELD_nodeRole
        FD_ISEDITABLE,    // FIELD_sequenceNumber
        FD_ISEDITABLE,    // FIELD_numNeighbors
        FD_ISEDITABLE,    // FIELD_timestamp
    };
    return (field >= 0 && field < 11) ? fieldTypeFlags[field] : 0;
}

const char *HelloPacketDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "nodeId",
        "posX",
        "posY",
        "posZ",
        "energy",
        "clusterId",
        "clusterHeadId",
        "nodeRole",
        "sequenceNumber",
        "numNeighbors",
        "timestamp",
    };
    return (field >= 0 && field < 11) ? fieldNames[field] : nullptr;
}

int HelloPacketDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "nodeId") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "posX") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "posY") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "posZ") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "energy") == 0) return baseIndex + 4;
    if (strcmp(fieldName, "clusterId") == 0) return baseIndex + 5;
    if (strcmp(fieldName, "clusterHeadId") == 0) return baseIndex + 6;
    if (strcmp(fieldName, "nodeRole") == 0) return baseIndex + 7;
    if (strcmp(fieldName, "sequenceNumber") == 0) return baseIndex + 8;
    if (strcmp(fieldName, "numNeighbors") == 0) return baseIndex + 9;
    if (strcmp(fieldName, "timestamp") == 0) return baseIndex + 10;
    return base ? base->findField(fieldName) : -1;
}

const char *HelloPacketDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",    // FIELD_nodeId
        "double",    // FIELD_posX
        "double",    // FIELD_posY
        "double",    // FIELD_posZ
        "double",    // FIELD_energy
        "int",    // FIELD_clusterId
        "int",    // FIELD_clusterHeadId
        "int",    // FIELD_nodeRole
        "int",    // FIELD_sequenceNumber
        "int",    // FIELD_numNeighbors
        "omnetpp::simtime_t",    // FIELD_timestamp
    };
    return (field >= 0 && field < 11) ? fieldTypeStrings[field] : nullptr;
}

const char **HelloPacketDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *HelloPacketDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int HelloPacketDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    HelloPacket *pp = omnetpp::fromAnyPtr<HelloPacket>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void HelloPacketDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    HelloPacket *pp = omnetpp::fromAnyPtr<HelloPacket>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'HelloPacket'", field);
    }
}

const char *HelloPacketDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    HelloPacket *pp = omnetpp::fromAnyPtr<HelloPacket>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string HelloPacketDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    HelloPacket *pp = omnetpp::fromAnyPtr<HelloPacket>(object); (void)pp;
    switch (field) {
        case FIELD_nodeId: return long2string(pp->getNodeId());
        case FIELD_posX: return double2string(pp->getPosX());
        case FIELD_posY: return double2string(pp->getPosY());
        case FIELD_posZ: return double2string(pp->getPosZ());
        case FIELD_energy: return double2string(pp->getEnergy());
        case FIELD_clusterId: return long2string(pp->getClusterId());
        case FIELD_clusterHeadId: return long2string(pp->getClusterHeadId());
        case FIELD_nodeRole: return long2string(pp->getNodeRole());
        case FIELD_sequenceNumber: return long2string(pp->getSequenceNumber());
        case FIELD_numNeighbors: return long2string(pp->getNumNeighbors());
        case FIELD_timestamp: return simtime2string(pp->getTimestamp());
        default: return "";
    }
}

void HelloPacketDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    HelloPacket *pp = omnetpp::fromAnyPtr<HelloPacket>(object); (void)pp;
    switch (field) {
        case FIELD_nodeId: pp->setNodeId(string2long(value)); break;
        case FIELD_posX: pp->setPosX(string2double(value)); break;
        case FIELD_posY: pp->setPosY(string2double(value)); break;
        case FIELD_posZ: pp->setPosZ(string2double(value)); break;
        case FIELD_energy: pp->setEnergy(string2double(value)); break;
        case FIELD_clusterId: pp->setClusterId(string2long(value)); break;
        case FIELD_clusterHeadId: pp->setClusterHeadId(string2long(value)); break;
        case FIELD_nodeRole: pp->setNodeRole(string2long(value)); break;
        case FIELD_sequenceNumber: pp->setSequenceNumber(string2long(value)); break;
        case FIELD_numNeighbors: pp->setNumNeighbors(string2long(value)); break;
        case FIELD_timestamp: pp->setTimestamp(string2simtime(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'HelloPacket'", field);
    }
}

omnetpp::cValue HelloPacketDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    HelloPacket *pp = omnetpp::fromAnyPtr<HelloPacket>(object); (void)pp;
    switch (field) {
        case FIELD_nodeId: return pp->getNodeId();
        case FIELD_posX: return pp->getPosX();
        case FIELD_posY: return pp->getPosY();
        case FIELD_posZ: return pp->getPosZ();
        case FIELD_energy: return pp->getEnergy();
        case FIELD_clusterId: return pp->getClusterId();
        case FIELD_clusterHeadId: return pp->getClusterHeadId();
        case FIELD_nodeRole: return pp->getNodeRole();
        case FIELD_sequenceNumber: return pp->getSequenceNumber();
        case FIELD_numNeighbors: return pp->getNumNeighbors();
        case FIELD_timestamp: return pp->getTimestamp().dbl();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'HelloPacket' as cValue -- field index out of range?", field);
    }
}

void HelloPacketDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    HelloPacket *pp = omnetpp::fromAnyPtr<HelloPacket>(object); (void)pp;
    switch (field) {
        case FIELD_nodeId: pp->setNodeId(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_posX: pp->setPosX(value.doubleValue()); break;
        case FIELD_posY: pp->setPosY(value.doubleValue()); break;
        case FIELD_posZ: pp->setPosZ(value.doubleValue()); break;
        case FIELD_energy: pp->setEnergy(value.doubleValue()); break;
        case FIELD_clusterId: pp->setClusterId(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_clusterHeadId: pp->setClusterHeadId(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_nodeRole: pp->setNodeRole(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_sequenceNumber: pp->setSequenceNumber(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_numNeighbors: pp->setNumNeighbors(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_timestamp: pp->setTimestamp(value.doubleValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'HelloPacket'", field);
    }
}

const char *HelloPacketDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

omnetpp::any_ptr HelloPacketDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    HelloPacket *pp = omnetpp::fromAnyPtr<HelloPacket>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void HelloPacketDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    HelloPacket *pp = omnetpp::fromAnyPtr<HelloPacket>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'HelloPacket'", field);
    }
}

Register_Class(TopologyUpdatePacket)

TopologyUpdatePacket::TopologyUpdatePacket() : ::inet::FieldsChunk()
{
}

TopologyUpdatePacket::TopologyUpdatePacket(const TopologyUpdatePacket& other) : ::inet::FieldsChunk(other)
{
    copy(other);
}

TopologyUpdatePacket::~TopologyUpdatePacket()
{
}

TopologyUpdatePacket& TopologyUpdatePacket::operator=(const TopologyUpdatePacket& other)
{
    if (this == &other) return *this;
    ::inet::FieldsChunk::operator=(other);
    copy(other);
    return *this;
}

void TopologyUpdatePacket::copy(const TopologyUpdatePacket& other)
{
    this->sourceId = other.sourceId;
    this->destId = other.destId;
    this->weight = other.weight;
    this->isActive_ = other.isActive_;
    this->sequenceNumber = other.sequenceNumber;
}

void TopologyUpdatePacket::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::FieldsChunk::parsimPack(b);
    doParsimPacking(b,this->sourceId);
    doParsimPacking(b,this->destId);
    doParsimPacking(b,this->weight);
    doParsimPacking(b,this->isActive_);
    doParsimPacking(b,this->sequenceNumber);
}

void TopologyUpdatePacket::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::FieldsChunk::parsimUnpack(b);
    doParsimUnpacking(b,this->sourceId);
    doParsimUnpacking(b,this->destId);
    doParsimUnpacking(b,this->weight);
    doParsimUnpacking(b,this->isActive_);
    doParsimUnpacking(b,this->sequenceNumber);
}

int TopologyUpdatePacket::getSourceId() const
{
    return this->sourceId;
}

void TopologyUpdatePacket::setSourceId(int sourceId)
{
    handleChange();
    this->sourceId = sourceId;
}

int TopologyUpdatePacket::getDestId() const
{
    return this->destId;
}

void TopologyUpdatePacket::setDestId(int destId)
{
    handleChange();
    this->destId = destId;
}

double TopologyUpdatePacket::getWeight() const
{
    return this->weight;
}

void TopologyUpdatePacket::setWeight(double weight)
{
    handleChange();
    this->weight = weight;
}

bool TopologyUpdatePacket::isActive() const
{
    return this->isActive_;
}

void TopologyUpdatePacket::setIsActive(bool isActive)
{
    handleChange();
    this->isActive_ = isActive;
}

int TopologyUpdatePacket::getSequenceNumber() const
{
    return this->sequenceNumber;
}

void TopologyUpdatePacket::setSequenceNumber(int sequenceNumber)
{
    handleChange();
    this->sequenceNumber = sequenceNumber;
}

class TopologyUpdatePacketDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_sourceId,
        FIELD_destId,
        FIELD_weight,
        FIELD_isActive,
        FIELD_sequenceNumber,
    };
  public:
    TopologyUpdatePacketDescriptor();
    virtual ~TopologyUpdatePacketDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyName) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyName) const override;
    virtual int getFieldArraySize(omnetpp::any_ptr object, int field) const override;
    virtual void setFieldArraySize(omnetpp::any_ptr object, int field, int size) const override;

    virtual const char *getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const override;
    virtual std::string getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const override;
    virtual omnetpp::cValue getFieldValue(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual omnetpp::any_ptr getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const override;
};

Register_ClassDescriptor(TopologyUpdatePacketDescriptor)

TopologyUpdatePacketDescriptor::TopologyUpdatePacketDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(mstclustering::TopologyUpdatePacket)), "inet::FieldsChunk")
{
    propertyNames = nullptr;
}

TopologyUpdatePacketDescriptor::~TopologyUpdatePacketDescriptor()
{
    delete[] propertyNames;
}

bool TopologyUpdatePacketDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<TopologyUpdatePacket *>(obj)!=nullptr;
}

const char **TopologyUpdatePacketDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *TopologyUpdatePacketDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int TopologyUpdatePacketDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 5+base->getFieldCount() : 5;
}

unsigned int TopologyUpdatePacketDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_sourceId
        FD_ISEDITABLE,    // FIELD_destId
        FD_ISEDITABLE,    // FIELD_weight
        FD_ISEDITABLE,    // FIELD_isActive
        FD_ISEDITABLE,    // FIELD_sequenceNumber
    };
    return (field >= 0 && field < 5) ? fieldTypeFlags[field] : 0;
}

const char *TopologyUpdatePacketDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "sourceId",
        "destId",
        "weight",
        "isActive",
        "sequenceNumber",
    };
    return (field >= 0 && field < 5) ? fieldNames[field] : nullptr;
}

int TopologyUpdatePacketDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "sourceId") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "destId") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "weight") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "isActive") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "sequenceNumber") == 0) return baseIndex + 4;
    return base ? base->findField(fieldName) : -1;
}

const char *TopologyUpdatePacketDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",    // FIELD_sourceId
        "int",    // FIELD_destId
        "double",    // FIELD_weight
        "bool",    // FIELD_isActive
        "int",    // FIELD_sequenceNumber
    };
    return (field >= 0 && field < 5) ? fieldTypeStrings[field] : nullptr;
}

const char **TopologyUpdatePacketDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *TopologyUpdatePacketDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int TopologyUpdatePacketDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    TopologyUpdatePacket *pp = omnetpp::fromAnyPtr<TopologyUpdatePacket>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void TopologyUpdatePacketDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    TopologyUpdatePacket *pp = omnetpp::fromAnyPtr<TopologyUpdatePacket>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'TopologyUpdatePacket'", field);
    }
}

const char *TopologyUpdatePacketDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    TopologyUpdatePacket *pp = omnetpp::fromAnyPtr<TopologyUpdatePacket>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string TopologyUpdatePacketDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    TopologyUpdatePacket *pp = omnetpp::fromAnyPtr<TopologyUpdatePacket>(object); (void)pp;
    switch (field) {
        case FIELD_sourceId: return long2string(pp->getSourceId());
        case FIELD_destId: return long2string(pp->getDestId());
        case FIELD_weight: return double2string(pp->getWeight());
        case FIELD_isActive: return bool2string(pp->isActive());
        case FIELD_sequenceNumber: return long2string(pp->getSequenceNumber());
        default: return "";
    }
}

void TopologyUpdatePacketDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    TopologyUpdatePacket *pp = omnetpp::fromAnyPtr<TopologyUpdatePacket>(object); (void)pp;
    switch (field) {
        case FIELD_sourceId: pp->setSourceId(string2long(value)); break;
        case FIELD_destId: pp->setDestId(string2long(value)); break;
        case FIELD_weight: pp->setWeight(string2double(value)); break;
        case FIELD_isActive: pp->setIsActive(string2bool(value)); break;
        case FIELD_sequenceNumber: pp->setSequenceNumber(string2long(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'TopologyUpdatePacket'", field);
    }
}

omnetpp::cValue TopologyUpdatePacketDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    TopologyUpdatePacket *pp = omnetpp::fromAnyPtr<TopologyUpdatePacket>(object); (void)pp;
    switch (field) {
        case FIELD_sourceId: return pp->getSourceId();
        case FIELD_destId: return pp->getDestId();
        case FIELD_weight: return pp->getWeight();
        case FIELD_isActive: return pp->isActive();
        case FIELD_sequenceNumber: return pp->getSequenceNumber();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'TopologyUpdatePacket' as cValue -- field index out of range?", field);
    }
}

void TopologyUpdatePacketDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    TopologyUpdatePacket *pp = omnetpp::fromAnyPtr<TopologyUpdatePacket>(object); (void)pp;
    switch (field) {
        case FIELD_sourceId: pp->setSourceId(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_destId: pp->setDestId(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_weight: pp->setWeight(value.doubleValue()); break;
        case FIELD_isActive: pp->setIsActive(value.boolValue()); break;
        case FIELD_sequenceNumber: pp->setSequenceNumber(omnetpp::checked_int_cast<int>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'TopologyUpdatePacket'", field);
    }
}

const char *TopologyUpdatePacketDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

omnetpp::any_ptr TopologyUpdatePacketDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    TopologyUpdatePacket *pp = omnetpp::fromAnyPtr<TopologyUpdatePacket>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void TopologyUpdatePacketDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    TopologyUpdatePacket *pp = omnetpp::fromAnyPtr<TopologyUpdatePacket>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'TopologyUpdatePacket'", field);
    }
}

Register_Class(ClusterJoinPacket)

ClusterJoinPacket::ClusterJoinPacket() : ::inet::FieldsChunk()
{
}

ClusterJoinPacket::ClusterJoinPacket(const ClusterJoinPacket& other) : ::inet::FieldsChunk(other)
{
    copy(other);
}

ClusterJoinPacket::~ClusterJoinPacket()
{
}

ClusterJoinPacket& ClusterJoinPacket::operator=(const ClusterJoinPacket& other)
{
    if (this == &other) return *this;
    ::inet::FieldsChunk::operator=(other);
    copy(other);
    return *this;
}

void ClusterJoinPacket::copy(const ClusterJoinPacket& other)
{
    this->nodeId = other.nodeId;
    this->clusterId = other.clusterId;
    this->clusterHeadId = other.clusterHeadId;
    this->energy = other.energy;
    this->sequenceNumber = other.sequenceNumber;
}

void ClusterJoinPacket::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::FieldsChunk::parsimPack(b);
    doParsimPacking(b,this->nodeId);
    doParsimPacking(b,this->clusterId);
    doParsimPacking(b,this->clusterHeadId);
    doParsimPacking(b,this->energy);
    doParsimPacking(b,this->sequenceNumber);
}

void ClusterJoinPacket::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::FieldsChunk::parsimUnpack(b);
    doParsimUnpacking(b,this->nodeId);
    doParsimUnpacking(b,this->clusterId);
    doParsimUnpacking(b,this->clusterHeadId);
    doParsimUnpacking(b,this->energy);
    doParsimUnpacking(b,this->sequenceNumber);
}

int ClusterJoinPacket::getNodeId() const
{
    return this->nodeId;
}

void ClusterJoinPacket::setNodeId(int nodeId)
{
    handleChange();
    this->nodeId = nodeId;
}

int ClusterJoinPacket::getClusterId() const
{
    return this->clusterId;
}

void ClusterJoinPacket::setClusterId(int clusterId)
{
    handleChange();
    this->clusterId = clusterId;
}

int ClusterJoinPacket::getClusterHeadId() const
{
    return this->clusterHeadId;
}

void ClusterJoinPacket::setClusterHeadId(int clusterHeadId)
{
    handleChange();
    this->clusterHeadId = clusterHeadId;
}

double ClusterJoinPacket::getEnergy() const
{
    return this->energy;
}

void ClusterJoinPacket::setEnergy(double energy)
{
    handleChange();
    this->energy = energy;
}

int ClusterJoinPacket::getSequenceNumber() const
{
    return this->sequenceNumber;
}

void ClusterJoinPacket::setSequenceNumber(int sequenceNumber)
{
    handleChange();
    this->sequenceNumber = sequenceNumber;
}

class ClusterJoinPacketDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_nodeId,
        FIELD_clusterId,
        FIELD_clusterHeadId,
        FIELD_energy,
        FIELD_sequenceNumber,
    };
  public:
    ClusterJoinPacketDescriptor();
    virtual ~ClusterJoinPacketDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyName) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyName) const override;
    virtual int getFieldArraySize(omnetpp::any_ptr object, int field) const override;
    virtual void setFieldArraySize(omnetpp::any_ptr object, int field, int size) const override;

    virtual const char *getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const override;
    virtual std::string getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const override;
    virtual omnetpp::cValue getFieldValue(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual omnetpp::any_ptr getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const override;
};

Register_ClassDescriptor(ClusterJoinPacketDescriptor)

ClusterJoinPacketDescriptor::ClusterJoinPacketDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(mstclustering::ClusterJoinPacket)), "inet::FieldsChunk")
{
    propertyNames = nullptr;
}

ClusterJoinPacketDescriptor::~ClusterJoinPacketDescriptor()
{
    delete[] propertyNames;
}

bool ClusterJoinPacketDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<ClusterJoinPacket *>(obj)!=nullptr;
}

const char **ClusterJoinPacketDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *ClusterJoinPacketDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int ClusterJoinPacketDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 5+base->getFieldCount() : 5;
}

unsigned int ClusterJoinPacketDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_nodeId
        FD_ISEDITABLE,    // FIELD_clusterId
        FD_ISEDITABLE,    // FIELD_clusterHeadId
        FD_ISEDITABLE,    // FIELD_energy
        FD_ISEDITABLE,    // FIELD_sequenceNumber
    };
    return (field >= 0 && field < 5) ? fieldTypeFlags[field] : 0;
}

const char *ClusterJoinPacketDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "nodeId",
        "clusterId",
        "clusterHeadId",
        "energy",
        "sequenceNumber",
    };
    return (field >= 0 && field < 5) ? fieldNames[field] : nullptr;
}

int ClusterJoinPacketDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "nodeId") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "clusterId") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "clusterHeadId") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "energy") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "sequenceNumber") == 0) return baseIndex + 4;
    return base ? base->findField(fieldName) : -1;
}

const char *ClusterJoinPacketDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",    // FIELD_nodeId
        "int",    // FIELD_clusterId
        "int",    // FIELD_clusterHeadId
        "double",    // FIELD_energy
        "int",    // FIELD_sequenceNumber
    };
    return (field >= 0 && field < 5) ? fieldTypeStrings[field] : nullptr;
}

const char **ClusterJoinPacketDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *ClusterJoinPacketDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int ClusterJoinPacketDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    ClusterJoinPacket *pp = omnetpp::fromAnyPtr<ClusterJoinPacket>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void ClusterJoinPacketDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    ClusterJoinPacket *pp = omnetpp::fromAnyPtr<ClusterJoinPacket>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'ClusterJoinPacket'", field);
    }
}

const char *ClusterJoinPacketDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    ClusterJoinPacket *pp = omnetpp::fromAnyPtr<ClusterJoinPacket>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string ClusterJoinPacketDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    ClusterJoinPacket *pp = omnetpp::fromAnyPtr<ClusterJoinPacket>(object); (void)pp;
    switch (field) {
        case FIELD_nodeId: return long2string(pp->getNodeId());
        case FIELD_clusterId: return long2string(pp->getClusterId());
        case FIELD_clusterHeadId: return long2string(pp->getClusterHeadId());
        case FIELD_energy: return double2string(pp->getEnergy());
        case FIELD_sequenceNumber: return long2string(pp->getSequenceNumber());
        default: return "";
    }
}

void ClusterJoinPacketDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    ClusterJoinPacket *pp = omnetpp::fromAnyPtr<ClusterJoinPacket>(object); (void)pp;
    switch (field) {
        case FIELD_nodeId: pp->setNodeId(string2long(value)); break;
        case FIELD_clusterId: pp->setClusterId(string2long(value)); break;
        case FIELD_clusterHeadId: pp->setClusterHeadId(string2long(value)); break;
        case FIELD_energy: pp->setEnergy(string2double(value)); break;
        case FIELD_sequenceNumber: pp->setSequenceNumber(string2long(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'ClusterJoinPacket'", field);
    }
}

omnetpp::cValue ClusterJoinPacketDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    ClusterJoinPacket *pp = omnetpp::fromAnyPtr<ClusterJoinPacket>(object); (void)pp;
    switch (field) {
        case FIELD_nodeId: return pp->getNodeId();
        case FIELD_clusterId: return pp->getClusterId();
        case FIELD_clusterHeadId: return pp->getClusterHeadId();
        case FIELD_energy: return pp->getEnergy();
        case FIELD_sequenceNumber: return pp->getSequenceNumber();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'ClusterJoinPacket' as cValue -- field index out of range?", field);
    }
}

void ClusterJoinPacketDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    ClusterJoinPacket *pp = omnetpp::fromAnyPtr<ClusterJoinPacket>(object); (void)pp;
    switch (field) {
        case FIELD_nodeId: pp->setNodeId(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_clusterId: pp->setClusterId(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_clusterHeadId: pp->setClusterHeadId(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_energy: pp->setEnergy(value.doubleValue()); break;
        case FIELD_sequenceNumber: pp->setSequenceNumber(omnetpp::checked_int_cast<int>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'ClusterJoinPacket'", field);
    }
}

const char *ClusterJoinPacketDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

omnetpp::any_ptr ClusterJoinPacketDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    ClusterJoinPacket *pp = omnetpp::fromAnyPtr<ClusterJoinPacket>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void ClusterJoinPacketDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    ClusterJoinPacket *pp = omnetpp::fromAnyPtr<ClusterJoinPacket>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'ClusterJoinPacket'", field);
    }
}

Register_Class(ClusterHeadPacket)

ClusterHeadPacket::ClusterHeadPacket() : ::inet::FieldsChunk()
{
}

ClusterHeadPacket::ClusterHeadPacket(const ClusterHeadPacket& other) : ::inet::FieldsChunk(other)
{
    copy(other);
}

ClusterHeadPacket::~ClusterHeadPacket()
{
}

ClusterHeadPacket& ClusterHeadPacket::operator=(const ClusterHeadPacket& other)
{
    if (this == &other) return *this;
    ::inet::FieldsChunk::operator=(other);
    copy(other);
    return *this;
}

void ClusterHeadPacket::copy(const ClusterHeadPacket& other)
{
    this->clusterId = other.clusterId;
    this->clusterHeadId = other.clusterHeadId;
    this->memberCount = other.memberCount;
    this->avgEnergy = other.avgEnergy;
    this->sequenceNumber = other.sequenceNumber;
}

void ClusterHeadPacket::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::FieldsChunk::parsimPack(b);
    doParsimPacking(b,this->clusterId);
    doParsimPacking(b,this->clusterHeadId);
    doParsimPacking(b,this->memberCount);
    doParsimPacking(b,this->avgEnergy);
    doParsimPacking(b,this->sequenceNumber);
}

void ClusterHeadPacket::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::FieldsChunk::parsimUnpack(b);
    doParsimUnpacking(b,this->clusterId);
    doParsimUnpacking(b,this->clusterHeadId);
    doParsimUnpacking(b,this->memberCount);
    doParsimUnpacking(b,this->avgEnergy);
    doParsimUnpacking(b,this->sequenceNumber);
}

int ClusterHeadPacket::getClusterId() const
{
    return this->clusterId;
}

void ClusterHeadPacket::setClusterId(int clusterId)
{
    handleChange();
    this->clusterId = clusterId;
}

int ClusterHeadPacket::getClusterHeadId() const
{
    return this->clusterHeadId;
}

void ClusterHeadPacket::setClusterHeadId(int clusterHeadId)
{
    handleChange();
    this->clusterHeadId = clusterHeadId;
}

int ClusterHeadPacket::getMemberCount() const
{
    return this->memberCount;
}

void ClusterHeadPacket::setMemberCount(int memberCount)
{
    handleChange();
    this->memberCount = memberCount;
}

double ClusterHeadPacket::getAvgEnergy() const
{
    return this->avgEnergy;
}

void ClusterHeadPacket::setAvgEnergy(double avgEnergy)
{
    handleChange();
    this->avgEnergy = avgEnergy;
}

int ClusterHeadPacket::getSequenceNumber() const
{
    return this->sequenceNumber;
}

void ClusterHeadPacket::setSequenceNumber(int sequenceNumber)
{
    handleChange();
    this->sequenceNumber = sequenceNumber;
}

class ClusterHeadPacketDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_clusterId,
        FIELD_clusterHeadId,
        FIELD_memberCount,
        FIELD_avgEnergy,
        FIELD_sequenceNumber,
    };
  public:
    ClusterHeadPacketDescriptor();
    virtual ~ClusterHeadPacketDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyName) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyName) const override;
    virtual int getFieldArraySize(omnetpp::any_ptr object, int field) const override;
    virtual void setFieldArraySize(omnetpp::any_ptr object, int field, int size) const override;

    virtual const char *getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const override;
    virtual std::string getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const override;
    virtual omnetpp::cValue getFieldValue(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual omnetpp::any_ptr getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const override;
};

Register_ClassDescriptor(ClusterHeadPacketDescriptor)

ClusterHeadPacketDescriptor::ClusterHeadPacketDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(mstclustering::ClusterHeadPacket)), "inet::FieldsChunk")
{
    propertyNames = nullptr;
}

ClusterHeadPacketDescriptor::~ClusterHeadPacketDescriptor()
{
    delete[] propertyNames;
}

bool ClusterHeadPacketDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<ClusterHeadPacket *>(obj)!=nullptr;
}

const char **ClusterHeadPacketDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *ClusterHeadPacketDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int ClusterHeadPacketDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 5+base->getFieldCount() : 5;
}

unsigned int ClusterHeadPacketDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_clusterId
        FD_ISEDITABLE,    // FIELD_clusterHeadId
        FD_ISEDITABLE,    // FIELD_memberCount
        FD_ISEDITABLE,    // FIELD_avgEnergy
        FD_ISEDITABLE,    // FIELD_sequenceNumber
    };
    return (field >= 0 && field < 5) ? fieldTypeFlags[field] : 0;
}

const char *ClusterHeadPacketDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "clusterId",
        "clusterHeadId",
        "memberCount",
        "avgEnergy",
        "sequenceNumber",
    };
    return (field >= 0 && field < 5) ? fieldNames[field] : nullptr;
}

int ClusterHeadPacketDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "clusterId") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "clusterHeadId") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "memberCount") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "avgEnergy") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "sequenceNumber") == 0) return baseIndex + 4;
    return base ? base->findField(fieldName) : -1;
}

const char *ClusterHeadPacketDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",    // FIELD_clusterId
        "int",    // FIELD_clusterHeadId
        "int",    // FIELD_memberCount
        "double",    // FIELD_avgEnergy
        "int",    // FIELD_sequenceNumber
    };
    return (field >= 0 && field < 5) ? fieldTypeStrings[field] : nullptr;
}

const char **ClusterHeadPacketDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *ClusterHeadPacketDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int ClusterHeadPacketDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    ClusterHeadPacket *pp = omnetpp::fromAnyPtr<ClusterHeadPacket>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void ClusterHeadPacketDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    ClusterHeadPacket *pp = omnetpp::fromAnyPtr<ClusterHeadPacket>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'ClusterHeadPacket'", field);
    }
}

const char *ClusterHeadPacketDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    ClusterHeadPacket *pp = omnetpp::fromAnyPtr<ClusterHeadPacket>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string ClusterHeadPacketDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    ClusterHeadPacket *pp = omnetpp::fromAnyPtr<ClusterHeadPacket>(object); (void)pp;
    switch (field) {
        case FIELD_clusterId: return long2string(pp->getClusterId());
        case FIELD_clusterHeadId: return long2string(pp->getClusterHeadId());
        case FIELD_memberCount: return long2string(pp->getMemberCount());
        case FIELD_avgEnergy: return double2string(pp->getAvgEnergy());
        case FIELD_sequenceNumber: return long2string(pp->getSequenceNumber());
        default: return "";
    }
}

void ClusterHeadPacketDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    ClusterHeadPacket *pp = omnetpp::fromAnyPtr<ClusterHeadPacket>(object); (void)pp;
    switch (field) {
        case FIELD_clusterId: pp->setClusterId(string2long(value)); break;
        case FIELD_clusterHeadId: pp->setClusterHeadId(string2long(value)); break;
        case FIELD_memberCount: pp->setMemberCount(string2long(value)); break;
        case FIELD_avgEnergy: pp->setAvgEnergy(string2double(value)); break;
        case FIELD_sequenceNumber: pp->setSequenceNumber(string2long(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'ClusterHeadPacket'", field);
    }
}

omnetpp::cValue ClusterHeadPacketDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    ClusterHeadPacket *pp = omnetpp::fromAnyPtr<ClusterHeadPacket>(object); (void)pp;
    switch (field) {
        case FIELD_clusterId: return pp->getClusterId();
        case FIELD_clusterHeadId: return pp->getClusterHeadId();
        case FIELD_memberCount: return pp->getMemberCount();
        case FIELD_avgEnergy: return pp->getAvgEnergy();
        case FIELD_sequenceNumber: return pp->getSequenceNumber();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'ClusterHeadPacket' as cValue -- field index out of range?", field);
    }
}

void ClusterHeadPacketDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    ClusterHeadPacket *pp = omnetpp::fromAnyPtr<ClusterHeadPacket>(object); (void)pp;
    switch (field) {
        case FIELD_clusterId: pp->setClusterId(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_clusterHeadId: pp->setClusterHeadId(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_memberCount: pp->setMemberCount(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_avgEnergy: pp->setAvgEnergy(value.doubleValue()); break;
        case FIELD_sequenceNumber: pp->setSequenceNumber(omnetpp::checked_int_cast<int>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'ClusterHeadPacket'", field);
    }
}

const char *ClusterHeadPacketDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

omnetpp::any_ptr ClusterHeadPacketDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    ClusterHeadPacket *pp = omnetpp::fromAnyPtr<ClusterHeadPacket>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void ClusterHeadPacketDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    ClusterHeadPacket *pp = omnetpp::fromAnyPtr<ClusterHeadPacket>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'ClusterHeadPacket'", field);
    }
}

Register_Class(EdgeInfoPacket)

EdgeInfoPacket::EdgeInfoPacket() : ::inet::FieldsChunk()
{
}

EdgeInfoPacket::EdgeInfoPacket(const EdgeInfoPacket& other) : ::inet::FieldsChunk(other)
{
    copy(other);
}

EdgeInfoPacket::~EdgeInfoPacket()
{
}

EdgeInfoPacket& EdgeInfoPacket::operator=(const EdgeInfoPacket& other)
{
    if (this == &other) return *this;
    ::inet::FieldsChunk::operator=(other);
    copy(other);
    return *this;
}

void EdgeInfoPacket::copy(const EdgeInfoPacket& other)
{
    this->sourceId = other.sourceId;
    this->destId = other.destId;
    this->weight = other.weight;
    this->mstId = other.mstId;
    this->sequenceNumber = other.sequenceNumber;
}

void EdgeInfoPacket::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::FieldsChunk::parsimPack(b);
    doParsimPacking(b,this->sourceId);
    doParsimPacking(b,this->destId);
    doParsimPacking(b,this->weight);
    doParsimPacking(b,this->mstId);
    doParsimPacking(b,this->sequenceNumber);
}

void EdgeInfoPacket::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::FieldsChunk::parsimUnpack(b);
    doParsimUnpacking(b,this->sourceId);
    doParsimUnpacking(b,this->destId);
    doParsimUnpacking(b,this->weight);
    doParsimUnpacking(b,this->mstId);
    doParsimUnpacking(b,this->sequenceNumber);
}

int EdgeInfoPacket::getSourceId() const
{
    return this->sourceId;
}

void EdgeInfoPacket::setSourceId(int sourceId)
{
    handleChange();
    this->sourceId = sourceId;
}

int EdgeInfoPacket::getDestId() const
{
    return this->destId;
}

void EdgeInfoPacket::setDestId(int destId)
{
    handleChange();
    this->destId = destId;
}

double EdgeInfoPacket::getWeight() const
{
    return this->weight;
}

void EdgeInfoPacket::setWeight(double weight)
{
    handleChange();
    this->weight = weight;
}

int EdgeInfoPacket::getMstId() const
{
    return this->mstId;
}

void EdgeInfoPacket::setMstId(int mstId)
{
    handleChange();
    this->mstId = mstId;
}

int EdgeInfoPacket::getSequenceNumber() const
{
    return this->sequenceNumber;
}

void EdgeInfoPacket::setSequenceNumber(int sequenceNumber)
{
    handleChange();
    this->sequenceNumber = sequenceNumber;
}

class EdgeInfoPacketDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_sourceId,
        FIELD_destId,
        FIELD_weight,
        FIELD_mstId,
        FIELD_sequenceNumber,
    };
  public:
    EdgeInfoPacketDescriptor();
    virtual ~EdgeInfoPacketDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyName) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyName) const override;
    virtual int getFieldArraySize(omnetpp::any_ptr object, int field) const override;
    virtual void setFieldArraySize(omnetpp::any_ptr object, int field, int size) const override;

    virtual const char *getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const override;
    virtual std::string getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const override;
    virtual omnetpp::cValue getFieldValue(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual omnetpp::any_ptr getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const override;
};

Register_ClassDescriptor(EdgeInfoPacketDescriptor)

EdgeInfoPacketDescriptor::EdgeInfoPacketDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(mstclustering::EdgeInfoPacket)), "inet::FieldsChunk")
{
    propertyNames = nullptr;
}

EdgeInfoPacketDescriptor::~EdgeInfoPacketDescriptor()
{
    delete[] propertyNames;
}

bool EdgeInfoPacketDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<EdgeInfoPacket *>(obj)!=nullptr;
}

const char **EdgeInfoPacketDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *EdgeInfoPacketDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int EdgeInfoPacketDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 5+base->getFieldCount() : 5;
}

unsigned int EdgeInfoPacketDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_sourceId
        FD_ISEDITABLE,    // FIELD_destId
        FD_ISEDITABLE,    // FIELD_weight
        FD_ISEDITABLE,    // FIELD_mstId
        FD_ISEDITABLE,    // FIELD_sequenceNumber
    };
    return (field >= 0 && field < 5) ? fieldTypeFlags[field] : 0;
}

const char *EdgeInfoPacketDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "sourceId",
        "destId",
        "weight",
        "mstId",
        "sequenceNumber",
    };
    return (field >= 0 && field < 5) ? fieldNames[field] : nullptr;
}

int EdgeInfoPacketDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "sourceId") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "destId") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "weight") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "mstId") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "sequenceNumber") == 0) return baseIndex + 4;
    return base ? base->findField(fieldName) : -1;
}

const char *EdgeInfoPacketDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",    // FIELD_sourceId
        "int",    // FIELD_destId
        "double",    // FIELD_weight
        "int",    // FIELD_mstId
        "int",    // FIELD_sequenceNumber
    };
    return (field >= 0 && field < 5) ? fieldTypeStrings[field] : nullptr;
}

const char **EdgeInfoPacketDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *EdgeInfoPacketDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int EdgeInfoPacketDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    EdgeInfoPacket *pp = omnetpp::fromAnyPtr<EdgeInfoPacket>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void EdgeInfoPacketDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    EdgeInfoPacket *pp = omnetpp::fromAnyPtr<EdgeInfoPacket>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'EdgeInfoPacket'", field);
    }
}

const char *EdgeInfoPacketDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    EdgeInfoPacket *pp = omnetpp::fromAnyPtr<EdgeInfoPacket>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string EdgeInfoPacketDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    EdgeInfoPacket *pp = omnetpp::fromAnyPtr<EdgeInfoPacket>(object); (void)pp;
    switch (field) {
        case FIELD_sourceId: return long2string(pp->getSourceId());
        case FIELD_destId: return long2string(pp->getDestId());
        case FIELD_weight: return double2string(pp->getWeight());
        case FIELD_mstId: return long2string(pp->getMstId());
        case FIELD_sequenceNumber: return long2string(pp->getSequenceNumber());
        default: return "";
    }
}

void EdgeInfoPacketDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    EdgeInfoPacket *pp = omnetpp::fromAnyPtr<EdgeInfoPacket>(object); (void)pp;
    switch (field) {
        case FIELD_sourceId: pp->setSourceId(string2long(value)); break;
        case FIELD_destId: pp->setDestId(string2long(value)); break;
        case FIELD_weight: pp->setWeight(string2double(value)); break;
        case FIELD_mstId: pp->setMstId(string2long(value)); break;
        case FIELD_sequenceNumber: pp->setSequenceNumber(string2long(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'EdgeInfoPacket'", field);
    }
}

omnetpp::cValue EdgeInfoPacketDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    EdgeInfoPacket *pp = omnetpp::fromAnyPtr<EdgeInfoPacket>(object); (void)pp;
    switch (field) {
        case FIELD_sourceId: return pp->getSourceId();
        case FIELD_destId: return pp->getDestId();
        case FIELD_weight: return pp->getWeight();
        case FIELD_mstId: return pp->getMstId();
        case FIELD_sequenceNumber: return pp->getSequenceNumber();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'EdgeInfoPacket' as cValue -- field index out of range?", field);
    }
}

void EdgeInfoPacketDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    EdgeInfoPacket *pp = omnetpp::fromAnyPtr<EdgeInfoPacket>(object); (void)pp;
    switch (field) {
        case FIELD_sourceId: pp->setSourceId(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_destId: pp->setDestId(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_weight: pp->setWeight(value.doubleValue()); break;
        case FIELD_mstId: pp->setMstId(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_sequenceNumber: pp->setSequenceNumber(omnetpp::checked_int_cast<int>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'EdgeInfoPacket'", field);
    }
}

const char *EdgeInfoPacketDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

omnetpp::any_ptr EdgeInfoPacketDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    EdgeInfoPacket *pp = omnetpp::fromAnyPtr<EdgeInfoPacket>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void EdgeInfoPacketDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    EdgeInfoPacket *pp = omnetpp::fromAnyPtr<EdgeInfoPacket>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'EdgeInfoPacket'", field);
    }
}

}  // namespace mstclustering

namespace omnetpp {

}  // namespace omnetpp

