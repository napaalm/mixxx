#pragma once

#include <QMainWindow>
#include <QSharedPointer>
#include <QString>
#include <memory>

#include "coreservices.h"
#include "preferences/configobject.h"
#include "preferences/constants.h"
#include "preferences/usersettings.h"
#include "soundio/sounddeviceerror.h"
#include "track/track_decl.h"
#include "util/cmdlineargs.h"
#include "util/db/dbconnectionpool.h"
#include "util/parented_ptr.h"
#include "util/timer.h"

class ChannelHandleFactory;
class ControlPushButton;
class ControllerManager;
class DlgDeveloperTools;
class DlgPreferences;
class EffectsManager;
class EngineMaster;
class GuiTick;
class VisualsManager;
class LaunchImage;
class Library;
class TrackCollectionManager;
class KeyboardEventFilter;
class PlayerManager;
class RecordingManager;
class SettingsManager;
class BroadcastManager;
class SkinLoader;
class SoundManager;
class SoundManagerConfig;
class VinylControlManager;
class WMainMenuBar;

typedef QSharedPointer<SettingsManager> SettingsManagerPointer;

// This Class is the base class for Mixxx. It sets up the main
// window and providing a menubar.
// For the main view, an instance of class MixxxView is
// created which creates your view.
class MixxxMainWindow : public QMainWindow {
    Q_OBJECT
  public:
    MixxxMainWindow(QApplication* app, std::shared_ptr<mixxx::CoreServices> pCoreServices);
    ~MixxxMainWindow() override;

#ifdef MIXXX_USE_QOPENGL
    void initializeQOpenGL();
#endif
    /// Initialize main window after creation. Should only be called once.
    void initialize();
    /// creates the menu_bar and inserts the file Menu
    void createMenuBar();
    void connectMenuBar();
    void setInhibitScreensaver(mixxx::ScreenSaverPreference inhibit);
    mixxx::ScreenSaverPreference getInhibitScreensaver();

    void setToolTipsCfg(mixxx::TooltipsPreference tt);
    inline mixxx::TooltipsPreference getToolTipsCfg() { return m_toolTipsCfg; }

    inline GuiTick* getGuiTick() { return m_pGuiTick; };

  public slots:
    void rebootMixxxView();

    void slotFileLoadSongPlayer(int deck);
    /// show the preferences dialog
    void slotOptionsPreferences();
    // shows an about dlg
    void slotHelpAbout();
    // toggle full screen mode
    void slotViewFullScreen(bool toggle);
    // Open the developer tools dialog.
    void slotDeveloperTools(bool enable);
    void slotDeveloperToolsClosed();

    void slotUpdateWindowTitle(TrackPointer pTrack);
    void slotChangedPlayingDeck(int deck);

    // Warn the user when inputs are not configured.
    void slotNoMicrophoneInputConfigured();
    void slotNoAuxiliaryInputConfigured();
    void slotNoDeckPassthroughInputConfigured();
    void slotNoVinylControlInputConfigured();

  signals:
    void skinLoaded();
    // used to uncheck the menu when the dialog of develeoper tools is closed
    void developerToolsDlgClosed(int r);
    void closeDeveloperToolsDlgChecked(int r);
    void fullScreenChanged(bool fullscreen);

  protected:
    // Event filter to block certain events (eg. tooltips if tooltips are disabled)
    bool eventFilter(QObject *obj, QEvent *event) override;
    void closeEvent(QCloseEvent *event) override;

  private slots:
    void initializationProgressUpdate(int progress, const QString& serviceName);

  private:
    void initializeWindow();
    void checkDirectRendering();

    /// Load skin to a QWidget that we set as the central widget.
    bool loadConfiguredSkin();

    bool confirmExit();
    QDialog::DialogCode soundDeviceErrorDlg(
            const QString &title, const QString &text, bool* retryClicked);
    QDialog::DialogCode soundDeviceBusyDlg(bool* retryClicked);
    QDialog::DialogCode soundDeviceErrorMsgDlg(
            SoundDeviceError err, bool* retryClicked);
    QDialog::DialogCode noOutputDlg(bool* continueClicked);

    std::shared_ptr<mixxx::CoreServices> m_pCoreServices;

    QWidget* m_pCentralWidget;
    LaunchImage* m_pLaunchImage;

    std::shared_ptr<SkinLoader> m_pSkinLoader;
    GuiTick* m_pGuiTick;
    VisualsManager* m_pVisualsManager;

    parented_ptr<WMainMenuBar> m_pMenuBar;

    DlgDeveloperTools* m_pDeveloperToolsDlg;

    /** Pointer to preference dialog */
    DlgPreferences* m_pPrefDlg;

    mixxx::TooltipsPreference m_toolTipsCfg;

    ControlPushButton* m_pTouchShift;
    mixxx::ScreenSaverPreference m_inhibitScreensaver;

    QSet<ControlObject*> m_skinCreatedControls;
};
