#ifndef AUDIOENGINE_H
#define AUDIOENGINE_H

#include <QAudio>
#include <QAudioDeviceInfo>
#include <QAudioInput>
#include <QByteArray>
#include <QTimer>
#include "spectrumanalyzer.h"

class QFile;
class QObject;

/******************************************************************************
 * Handles audio recording and management of the samples for analysis by the
 * frequency spectrum analyzer.
******************************************************************************/

class AudioEngine : public QObject
{
	Q_OBJECT
public:
	explicit AudioEngine(QObject *parent = 0);
	~AudioEngine();

	void startRecording();
	void stopRecording();

signals:
	void spectrumChanged(const FrequencySpectrum &spectrum);

public slots:
	void audioDataReady();

private:
	void calculateSpectrum(qint64 position);

private slots:
    void reset();

private:
	QAudioInput *mAudioInput;
	QIODevice *mAudioInputIODevice;
    QTimer *resetTimer;

	QByteArray mBuffer;
	qint64 mBufferHead;
	qint64 mBufferTail;
	qint64 mBufferLength;
	qint64 mBufferDataLength;

	QByteArray mSpectrumBuffer;
	qint64 mSpectrumBufferLength;
	SpectrumAnalyzer mSpectrumAnalyzer;
};

#endif // AUDIOENGINE_H
