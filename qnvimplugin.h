#pragma once

#include "qnvim_global.h"
#include <QColor>
#include <QPoint>
#include <QRect>

#include <extensionsystem/iplugin.h>

namespace Core {
class IEditor;
}

namespace NeovimQt {
class NeovimConnector;
}

namespace QNVim {
namespace Internal {

class QNVimPlugin : public ExtensionSystem::IPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QtCreatorPlugin" FILE "QNVim.json")

public:
    QNVimPlugin();
    ~QNVimPlugin();
    
    bool initialize(const QStringList &, QString *);
    bool initialize();
    void extensionsInitialized();
    ShutdownFlag aboutToShutdown();

    bool eventFilter(QObject *, QEvent *);
    void toggleQNVim();

protected:
    QString filename(Core::IEditor * = NULL) const;
    
    void fixSize(Core::IEditor * = NULL);
    void syncToVim();
    void syncFromVim();

private:

    void editorOpened(Core::IEditor *);
    void editorAboutToClose(Core::IEditor *);

    void handleNotification(const QByteArray &, const QVariantList &);
    void redraw(const QVariantList &);

    bool mEnabled;

    NeovimQt::NeovimConnector *mNVim;
    unsigned mVimChanges;
    QMap<QString, Core::IEditor *> mEditors;
    QMap<QString, unsigned long long> mBuffers;

    unsigned mWidth, mHeight;
    QColor mForegroundColor, mBackgroundColor, mSpecialColor;
    QColor mCursorColor;
    bool mBusy;
    bool mMouse;
    QByteArray mMode;
    QPoint mCursor;

    QRect mScrollRegion;
};

} // namespace Internal
} // namespace QNVim