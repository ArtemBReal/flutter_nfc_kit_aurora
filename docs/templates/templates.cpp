#include "templates.h"

/*********************************************************  
    Шаблонные представления основных классов и методов
    платформозависимой части плагина
**********************************************************/

//------------------ DBus iFace Declaration -----------------------------
class NfcdFooInterface : public QDBusAbstractInterface
{
    Q_OBJECT

public:
    NfcdFooInterface(QObject *parent = nullptr);

public slots:
    QDBusPendingReply<int> GetFooVersion();
    QDBusPendingReply<QList<QDBusObjectPath>> GetFooChlidren();
    //..................................//

signals:
    void FooChildrenChanged(const QList<QDBusObjectPath> &fooChildren);
};


//---------------- DBus iFace Definition -------------------------
NfcdFooDBusIface::NfcdFooInterface(QObject * parent) : 
QDBusAbstractInterface(NfcdConstants::nfcdService,
                        NfcdConstants::servicePath,
                        NfcdConstants::nfcdFooIFace,
                        QDBusConnection::systemBus(), parent)
{
    // empty
}

QDBusPendingReply<int> NfcdFooDBusIface::GetFooVersion()
{
    return asyncCallWithArgumentList(QStringLiteral("GetFooVersion"), QList<QVariant>());
}

QDBusPendingReply<QList<QDBusObjectPath>> NfcdFooDBusIface::GetFooChildren(){
 return asyncCallWithArgumentList(QStringLiteral("GetFooChildren"), QList<QVariant>());
}


//--------------- NFCD_Handler Private Declaration ------------------------
class NfcdFooHandlerPrivate : public QObject
{
    Q_OBJECT

public:
    explicit NfcdFooHandlerPrivate(QObject *parent = nullptr);

    QString fooVersion();
    QString fooChildrenList();
    NfcdFooChildrenModel *fooChildrenModel();
    //..................................//

private:
    QSharedPointer<NfcdFooDBusIface> m_iface{ nullptr };
    QSharedPointer<NfcdFooChildModel> m_model{ nullptr };
};

//--------------- NFCD_Handler Private Definition --------------------
NfcdFooHandlerPrivate::NfcdFooHandlerPrivate(QObject *parent) : QObject(parent),
                                            m_iface(new NfcdFooDBusIface(this)),
                                            m_model(new NfcdFooChildrenModel(
                                                new NfcdFooChildrenModelPrivate(m_iface.data()), 
                                                this)
                                            )
{
    // empty
}

QString NfcdFooHandlerPrivate::fooVersion(){
    return QStringLiteral("%1").arg(m_iface->GetFooVersion().value());
}

QString NfcdDaemonHandlerPrivate::fooChildrenList(){
    QList<QDBusObjectPath> reply = m_iface->GetFooChildren().value();
    QString fooChildrenList;

    for (const auto &fooChild : reply){
        fooChildrenList += fooChild.path();
        fooChildrenList += QStringLiteral("&");
    }
    return fooChildrenList;
}


//--------------- NFCD_Model Private Declaration ---------------------------
class NfcdFooChildrenModel;

class NfcdFooChildrenModelPrivate : public QObject
{
    Q_OBJECT

public:
    enum Role {
        PathRole = Qt::UserRole + 1,
        anyFooChildRole,
    };

public:
    NfcdFooChildrenModelPrivate(NfcdFooDBusIface *iface);

    void setParent(NfcdFooChildrenModel *parent);

    QHash<int, QByteArray> roleNames() const;
    QVariant data(const QModelIndex &index, int role) const;
    int rowCount(const QModelIndex &parent) const;

private slots:
    void updateFooChildern(const QList<QDBusObjectPath> &fooChildren;

private:
    NfcdFooChildrenModel *m_parent{ nullptr };
    NfcdFooDBusIface *m_foo{ nullptr };
    QMap<QString, QSharedPointer<NfcdFooChildDBusIface>> m_fooChildren{};
    QHash<int, QByteArray> m_roleNames{};
};


//--------------- NFCD_Model Private Definition ---------------------- 
NfcdFooChildrenModelPrivate::NfcdFooChildrenModelPrivate(NfcdFooDBusIface *iface) : QObject(nullptr), m_foo(iface)
{
    m_roleNames[NfcdFooChildrenModelPrivate::PathRole] = QByteArrayLiteral("path");
    m_roleNames[NfcdFooChildrenModelPrivate::anyFooChildRole] = QByteArrayLiteral("anyRole");

    updateFooChildren(iface->GetFooChildren().value());

    connect(iface, &NfcdFooDBusIface::FooChildrenChanged,
            this,
            &NfcdFooChildrenPrivate::updateFooChildren);
}

void NfcdFooChildrenModelPrivate::updateFooChildren(const QList<QDBusObjectPath> &fooChildren){
    QStringList fooChildrenPaths;

    for (const auto &fooChild : fooChildren){
        fooChildrenPaths.append(fooChild.path());
    }

    if (m_parent){
        m_parent->beginResetModel();
    }

    for (const auto &fooChildPath : fooChildrenPaths){
        if (m_fooChildren.contains(fooChildPath)){
            continue;
        }

        QSharedPointer<NfcdFooChildDBusIface> fooChildPtr(new NfcdFooChildDBusIface(fooChildPath));
        m_fooChildren.insert(fooChildPath, fooChildPtr);

        connect(fooChildPtr.data(), &NfcdFooChildDBusIface::anyFooChildPropChanged,
                [this](){
                    if (m_parent){
                        m_parent->beginResetModel();
                        m_parent->endResetModel();
                    }
                });
    }

    QMapIterator<QString, QSharedPointer<NfcdFooChildDBusIface>> it(m_fooChildren);
    while (it.hasNext()){
        it.next();
        if (fooChildrenPaths.contains(it.key())){
            continue;
        }

        m_fooChildren.take(it.key()).reset();
    }

    if (m_parent){
        m_parent->endResetModel();
    }
}

void NfcdFooChildrenModelPrivate::setParent(NfcdFooChildrenModel *parent){
    QObject::setParent(parent);
    m_parent = parent;
}

QHash<int, QByteArray> NfcdFooChildrenModelPrivate::roleNames() const {
    return m_roleNames;
}

QVariant NfcdFooChildrenModelPrivate::data(const QModelIndex &index, int role) const {
    if (index.row() >= m_fooChildren.count()){
        return QVariant();
    }

    auto key = m_fooChildren.keys().at(index.row());
    auto value = m_fooChildren.value(key);
    if (role == NfcdFooChildrenModelPrivate::PathRole){
        return key;
    }
    else if (role == NfcdFooChildrenModelPrivate::anyFooChildRole){
        return value->GetAnyFooChildProp().value();
    }
    return QVariant();
}

int NfcdFooChildrenModelPrivate::rowCount(const QModelIndex &parent) const {
    if (parent.isValid()){
        return 0;
    }

    return m_fooChildren.count();
}



//--------------- NFCD_Model Public Declaration ---------------------------- 
class NfcdFooChilderModelPrivate;

class NfcdFooChildrenModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit NfcdFooChildrenModel(QObject *parent = nullptr) = delete;
    NfcdFooChildrenModel(NfcdFooChildrenModelPrivate *data, QObject *parent = nullptr);

    QHash<int, QByteArray> roleNames() const override;
    QVariant data(const QModelIndex &index, int role) const override;
    int rowCount(const QModelIndex &parent) const override;

private:
    friend class NfcdFooChildrenModelPrivate;
    QSharedPointer<NfcdFooChildrenModelPrivate> m_data{ nullptr };
};


//--------------- NFCD_Model Public Definition ------------------------ 
NfcdFooChildrenModel::NfcdFooChildrenModel(NfcdFooChildrenModelPrivate *data, 
                                            QObject *parent)   
                                            : QAbstractListModel(parent), m_data(data){
    m_data->setParent(this);
}

QHash<int, QByteArray> NfcdFooChildrenModel::roleNames() const{
    return m_data->roleNames();
}

QVariant NfcdFooChildrenModel::data(const QModelIndex &index, int role) const{
    return m_data->data(index, role);
}

int NfcdFooChildrenModel::rowCount(const QModelIndex &parent) const{
    return m_data->rowCount(parent);
}

//--------------- NFCD_Handler Public Declaration ---------------------------
class NfcdFooHandlerPrivate;

class NfcdFooHandler : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString fooVersion READ fooVersion CONSTANT)
    Q_PROPERTY(QString fooChildrenList READ fooChildrenList CONSTANT)
    Q_PROPERTY(NfcdFooChildrenModel *fooChildrenModel READ fooChildrenModel CONSTANT)

public:
    explicit NfcdFooHandler(QObject *parent = nullptr);

    QString fooVersion();
    QString fooChildrenList();
    NfcdFooChildrenModel *fooChildrenModel();

private:
    QSharedPointer<NfcdFooHandlerPrivate> m_data{ nullptr };
};


//--------------- NFCD_Handler Public Definition -----------------------
NfcdFooHandler::NfcdFooHandler(QObject *parent) : QObject(parent), m_data(new NfcdFooHandlerPrivate(this))
{
    // empty
}

QString NfcdFooHandler::fooVersion(){
    return m_data->fooVersion();
}

QString NfcdFooHandler::fooChildrenList(){
    return m_data->fooChildrenList();
}


NfcdFooHandler *NfcdFooHandler::fooChildrenModel(){
    return m_data->fooChildrenModel();
}




//********************************* PLATFROM CHANNEL *****************************************


//---------------------------------  Platform Channel Declaration ----------------------------
class PLUGIN_EXPORT FlutterNfcKitAuroraPlugin final : public QObject, public PluginInterface
{
    Q_OBJECT

public:
    explicit FlutterNfcKitAuroraPlugin(QObject *parent = nullptr);
    void RegisterWithRegistrar(PluginRegistrar &registrar) override;

public slots:
    void checkSmthStatus();

private:
    void onMethodCall(const MethodCall &call);
    void unimplemented(const MethodCall &call);
    void onListen();
    void onCancel();

    bool getSmthStatus();

    bool m_sendEvents;

    static NfcdFooHandler& fooHandlerInstance();

    void onFooVersion(const MethodCall &call);

    QMetaObject::Connection m_smthStatusChangedConnection;

};


//---------------------------------  Platform Channel Definition ----------------------------
namespace Event
{
    constexpr auto Channel = "flutter_nfc_kit_aurora_events";
}

FlutterNfcKitAuroraPlugin::FlutterNfcKitAuroraPlugin(QObject *parent) : QObject(parent)
{
    m_sendEvents = false;
}

void FlutterNfcKitAuroraPlugin::RegisterWithRegistrar(PluginRegistrar &registrar)
{

    registrar.RegisterMethodChannel("flutter_nfc_kit_aurora",
                                    MethodCodecType::Standard,
                                    [this](const MethodCall &call)
                                    { this->onMethodCall(call); });
    registrar.RegisterEventChannel(
        Event::Channel,
        MethodCodecType::Standard,
        [this](const Encodable &)
        {
            this->onListen();
            return EventResponse();
        },
        [this](const Encodable &)
        {
            this->onCancel();
            return EventResponse();
        });
}


void FlutterNfcKitAuroraPlugin::onMethodCall(const MethodCall &call)
{
    const auto &method = call.GetMethod();

    if (method.find("Foo") != std::string::npos){
        if (method == "getFooVersion"){
            onGetFooVersion(call);
        }
        else if (...){
            //............
        }
        else {
            //............
        }
    }
    else if (...){
        //............
    }
    else {
        unimplemented(call);
    }
}

void FlutterNfcKitAuroraPlugin::unimplemented(const MethodCall &call)
{
    call.SendSuccessResponse(nullptr);
}

NfcdDaemonHandler &FlutterNfcKitAuroraPlugin::fooHandlerInstance()
{
    static NfcdFooHandler fooHandler;
    return fooHandler;
}

void FlutterNfcKitAuroraPlugin::onGetFooVersion(const MethodCall &call)
{
    QString fooVersion;
    fooVersion = FlutterNfcKitAuroraPlugin::fooHandlerInstance().fooVersion();

    call.SendSuccessResponse(fooVersion.toStdString());
}


void FlutterNfcKitAuroraPlugin::onListen()
{
    m_tagPresentChangedConnection =
        QObject::connect(&FlutterNfcKitAuroraPlugin::adapterHandlerInstance(),
                         &NfcdAdapterHandler::targetPresentChanged,
                         this,
                         &FlutterNfcKitAuroraPlugin::checkTargetPresent);

    m_adapterEnabledChangedConnection =
        QObject::connect(&FlutterNfcKitAuroraPlugin::adapterHandlerInstance(),
                         &NfcdAdapterHandler::enabledChanged,
                         this,
                         &FlutterNfcKitAuroraPlugin::checkAdapterEnabled);

    m_adapterPoweredChangedConnection =
        QObject::connect(&FlutterNfcKitAuroraPlugin::adapterHandlerInstance(),
                         &NfcdAdapterHandler::poweredChanged,
                         this,
                         &FlutterNfcKitAuroraPlugin::checkAdapterPowered);

    m_sendEvents = true;
    qDebug() << m_sendEvents;

    checkTargetPresent();
}

void FlutterNfcKitAuroraPlugin::onCancel()
{
    m_sendEvents = false;
    QObject::disconnect(m_tagPresentChangedConnection);
    QObject::disconnect(m_adapterEnabledChangedConnection);
    QObject::disconnect(m_adapterPoweredChangedConnection);
}

void FlutterNfcKitAuroraPlugin::checkTargetPresent()
{
    qDebug() << "Have Event";
    if (m_sendEvents)
    {
        qDebug() << "Sending event";
        auto whichEvent = QStringLiteral("targetPresented");
        EventChannel(Event::Channel, MethodCodecType::Standard).SendEvent(whichEvent.toStdString());
    }
}





