#ifndef SoundPLUGIN_H
#define SoundPLUGIN_H

#include "../interfaces/pluginsiteminterface.h"
#include "sounditem.h"
#include "soundapplet.h"
#include <QObject>

namespace dtb {
namespace sound {

class SoundPlugin : public QObject, public PluginsItemInterface
{
    Q_OBJECT
public:
    SoundPlugin();

    const QString pluginName() const Q_DECL_OVERRIDE;
    void init(PluginProxyInterface *proxyInter) Q_DECL_OVERRIDE;

    int itemSortKey(const QString &itemKey) Q_DECL_OVERRIDE;

    QWidget *itemWidget(const QString &itemKey) Q_DECL_OVERRIDE;
    QWidget *itemPopupApplet(const QString &itemKey) Q_DECL_OVERRIDE;

    const QString itemCommand(const QString &itemKey) Q_DECL_OVERRIDE;

    void popupShow() Q_DECL_OVERRIDE;
    void popupHide() Q_DECL_OVERRIDE;

    QMenu* itemContextMenu(const QString &itemKey) Q_DECL_OVERRIDE;

private:
    PluginProxyInterface *m_proxyInter;
    SoundItem *m_soundItem;
    QMenu *m_menu;
};
}
}

#endif // SoundPLUGIN_H
