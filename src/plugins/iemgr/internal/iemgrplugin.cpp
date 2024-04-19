#include "iemgrplugin.h"

#include <QApplication>
#include <QThread>

#include <QMCore/qmsystem.h>
#include <QMWidgets/qmdecoratorv2.h>

#include <extensionsystem/pluginspec.h>

#include <coreplugin/icore.h>
#include <coreplugin/initroutine.h>
#include <coreplugin/iprojectwindow.h>

#include "wizardmanager.h"
#include "homeaddon.h"

#include "midiwizard.h"
#include "opensvipwizard.h"
#include "svipwizard.h"
#include "ustwizard.h"

CK_STATIC_ACTION_EXTENSION_GETTER(iemgr_actions, getMyActionExtension);

namespace IEMgr::Internal {

    static WizardManager *imgr = nullptr;

    IEMgrPlugin::IEMgrPlugin() {
    }

    IEMgrPlugin::~IEMgrPlugin() {
    }

    bool IEMgrPlugin::initialize(const QStringList &arguments, QString *errorMessage) {
        // Add resources
        qIDec->addTranslationPath(pluginSpec()->location() + "/translations");
        qIDec->addThemePath(pluginSpec()->location() + "/themes");

        auto splash = Core::InitRoutine::splash();
        splash->showMessage(tr("Initializing import/export manager..."));

        // Init WizardManager instance
        imgr = new WizardManager(this);

        auto icore = Core::ICore::instance();

        // Add basic actions
        icore->actionDomain()->addExtension(getMyActionExtension());

        // Add basic windows and add-ons
        auto winMgr = icore->windowSystem();
        winMgr->addAddOn<HomeAddOn>(QStringLiteral("home"));

        // Add wizards
        imgr->addWizard(new MidiWizard());
        imgr->addWizard(new UstWizard());
        imgr->addWizard(new OpenSvipWizard());
        imgr->addWizard(new SvipWizard());

        return true;
    }

    void IEMgrPlugin::extensionsInitialized() {
    }

    bool IEMgrPlugin::delayedInitialize() {
        return false;
    }

}
