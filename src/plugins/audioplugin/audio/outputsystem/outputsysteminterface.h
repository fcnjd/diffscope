#ifndef AUDIO_OUTPUTSYSTEMINTERFACE_H
#define AUDIO_OUTPUTSYSTEMINTERFACE_H

#include <QObject>

namespace talcs {
    class AudioDriverManager;
    class AudioDriver;
    class AudioDevice;
    class MixerAudioSource;
}

namespace Audio {

    class AbstractOutputSystem;

    class AudioPlugin;

    class IOutputSystemAddOn;

    class OutputSystemInterfacePrivate;

    class OutputSystemInterface : public QObject {
        Q_OBJECT
        Q_DECLARE_PRIVATE(OutputSystemInterface)
        friend class AudioPlugin;
        friend class IOutputSystemAddOn;
    public:
        ~OutputSystemInterface() override;

        bool isVST() const;
        talcs::AudioDriverManager *audioDriverManager() const;
        talcs::AudioDriver *audioDriver() const;
        talcs::AudioDevice *audioDevice() const;
        talcs::MixerAudioSource *preMixer() const;

        bool isSourceSubstituted() const;

        bool makeReady();

    private:
        explicit OutputSystemInterface(AbstractOutputSystem *abstractOutputSystem, bool isVST, QObject *parent = nullptr);
        QScopedPointer<OutputSystemInterfacePrivate> d_ptr;
    };

} // Audio

#endif // AUDIO_OUTPUTSYSTEMINTERFACE_H
