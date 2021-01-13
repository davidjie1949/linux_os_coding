#include <QtQml/qqmlprivate.h>
#include <QtCore/qdir.h>
#include <QtCore/qurl.h>

static const unsigned char qt_resource_tree[] = {
0,
0,0,0,0,2,0,0,0,7,0,0,0,1,0,0,0,
52,0,0,0,0,0,1,0,0,0,0,0,0,0,92,0,
0,0,0,0,1,0,0,0,0,0,0,0,140,0,0,0,
0,0,1,0,0,0,0,0,0,0,8,0,0,0,0,0,
1,0,0,0,0,0,0,0,158,0,0,0,0,0,1,0,
0,0,0,0,0,0,192,0,0,0,0,0,1,0,0,0,
0,0,0,0,26,0,0,0,0,0,1,0,0,0,0};
static const unsigned char qt_resource_names[] = {
0,
1,0,0,0,47,0,47,0,6,5,187,88,60,0,84,0,
120,0,46,0,113,0,109,0,108,0,10,10,49,25,60,0,
67,0,105,0,114,0,99,0,108,0,101,0,46,0,113,0,
109,0,108,0,17,1,170,167,188,0,67,0,105,0,114,0,
99,0,108,0,101,0,70,0,111,0,114,0,109,0,46,0,
117,0,105,0,46,0,113,0,109,0,108,0,21,4,218,160,
124,0,66,0,97,0,99,0,107,0,103,0,114,0,111,0,
117,0,110,0,100,0,70,0,111,0,114,0,109,0,46,0,
117,0,105,0,46,0,113,0,109,0,108,0,6,5,155,88,
60,0,82,0,120,0,46,0,113,0,109,0,108,0,14,7,
4,152,252,0,66,0,97,0,99,0,107,0,103,0,114,0,
111,0,117,0,110,0,100,0,46,0,113,0,109,0,108,0,
8,8,1,90,92,0,109,0,97,0,105,0,110,0,46,0,
113,0,109,0,108};
static const unsigned char qt_resource_empty_payout[] = { 0, 0, 0, 0, 0 };
QT_BEGIN_NAMESPACE
extern Q_CORE_EXPORT bool qRegisterResourceData(int, const unsigned char *, const unsigned char *, const unsigned char *);
QT_END_NAMESPACE
namespace QmlCacheGeneratedCode {
namespace _0x5f__main_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _0x5f__Background_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _0x5f__Rx_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _0x5f__BackgroundForm_ui_0x2e_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _0x5f__CircleForm_ui_0x2e_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _0x5f__Circle_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _0x5f__Tx_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}

}
namespace {
struct Registry {
    Registry();
    ~Registry();
    QHash<QString, const QQmlPrivate::CachedQmlUnit*> resourcePathToCachedUnit;
    static const QQmlPrivate::CachedQmlUnit *lookupCachedUnit(const QUrl &url);
};

Q_GLOBAL_STATIC(Registry, unitRegistry)


Registry::Registry() {
        resourcePathToCachedUnit.insert(QStringLiteral("/main.qml"), &QmlCacheGeneratedCode::_0x5f__main_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/Background.qml"), &QmlCacheGeneratedCode::_0x5f__Background_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/Rx.qml"), &QmlCacheGeneratedCode::_0x5f__Rx_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/BackgroundForm.ui.qml"), &QmlCacheGeneratedCode::_0x5f__BackgroundForm_ui_0x2e_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/CircleForm.ui.qml"), &QmlCacheGeneratedCode::_0x5f__CircleForm_ui_0x2e_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/Circle.qml"), &QmlCacheGeneratedCode::_0x5f__Circle_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/Tx.qml"), &QmlCacheGeneratedCode::_0x5f__Tx_qml::unit);
    QQmlPrivate::RegisterQmlUnitCacheHook registration;
    registration.version = 0;
    registration.lookupCachedQmlUnit = &lookupCachedUnit;
    QQmlPrivate::qmlregister(QQmlPrivate::QmlUnitCacheHookRegistration, &registration);
QT_PREPEND_NAMESPACE(qRegisterResourceData)(/*version*/0x01, qt_resource_tree, qt_resource_names, qt_resource_empty_payout);
}

Registry::~Registry() {
    QQmlPrivate::qmlunregister(QQmlPrivate::QmlUnitCacheHookRegistration, quintptr(&lookupCachedUnit));
}

const QQmlPrivate::CachedQmlUnit *Registry::lookupCachedUnit(const QUrl &url) {
    if (url.scheme() != QLatin1String("qrc"))
        return nullptr;
    QString resourcePath = QDir::cleanPath(url.path());
    if (resourcePath.isEmpty())
        return nullptr;
    if (!resourcePath.startsWith(QLatin1Char('/')))
        resourcePath.prepend(QLatin1Char('/'));
    return unitRegistry()->resourcePathToCachedUnit.value(resourcePath, nullptr);
}
}
int QT_MANGLE_NAMESPACE(qInitResources_qml)() {
    ::unitRegistry();
    return 1;
}
Q_CONSTRUCTOR_FUNCTION(QT_MANGLE_NAMESPACE(qInitResources_qml))
int QT_MANGLE_NAMESPACE(qCleanupResources_qml)() {
    return 1;
}
