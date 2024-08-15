#ifndef MUSICMANAGER_H_
#define MUSICMANAGER_H_

#include <QMediaPlayer>
#include <QAudioOutput>
#include <QUrl>

class MusicManager {
public:
    static MusicManager& instance() {
        static MusicManager instance;
        return instance;
    }

    void play(const QString& musicFilePath) {
        if (!player) {
            player = new QMediaPlayer;
            audioOutput = new QAudioOutput;
            player->setAudioOutput(audioOutput);
            audioOutput->setVolume(0.5);
        }
        player->setSource(QUrl::fromLocalFile(musicFilePath));
        player->play();
    }

private:
    MusicManager() = default;
    ~MusicManager() {
        delete player;
        delete audioOutput;
    }

    MusicManager(const MusicManager&) = delete;
    MusicManager& operator=(const MusicManager&) = delete;

    QMediaPlayer* player = nullptr;
    QAudioOutput* audioOutput = nullptr;
};

#endif // MUSICMANAGER_H_