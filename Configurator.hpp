/*
 * File:    Configurator.hpp
 * Author:  Spiros
 *
 * Created on Jun 10, 2018, 5:28 PM
 */

#ifndef Configurator_HPP
#define Configurator_HPP

#include <QObject>
#include <QUrl>
#include <memory>
#include <AubioWrapper.hpp>
#include <NotesController.hpp>
#include <PitchBuffer.hpp>

class Configurator : public QObject {

    Q_OBJECT
    Q_PROPERTY(bool active MEMBER activeTuner WRITE setActive NOTIFY activeChanged())
    Q_PROPERTY(QString note MEMBER closestNote READ getClosestNote() NOTIFY samplesAnalyzed())
    Q_PROPERTY(qreal percentage MEMBER percentageOfDistanceFromTheClosestNote READ getPercentageOfDistanceFromTheClosestNote() NOTIFY samplesAnalyzed())
    Q_PROPERTY(qreal frequency MEMBER lastConfidentFrequency READ getFrequency() NOTIFY samplesAnalyzed())
    Q_PROPERTY(quint16 baseFreq READ getBaseFrequency() WRITE setBaseFrequency NOTIFY baseFrequencyChanged())
    Q_PROPERTY(QString setterName READ getOrganSetter() WRITE setOrganSetter NOTIFY organSetterChanged())

public:
    explicit Configurator(QObject *parent = nullptr);

    /**
     * @brief setActive this function activates and deactivates the tuner
     * @param active is a variable indicates if the tuner is gonna be active or not
     */
    void setActive(bool active);

    /**
     * @brief setOrganSetter is a function that sets the organ setter that is gonna be used
     * @param setter is the setter that defines the organSetter
     * freeMode
     * celloX where x {1-4} check below what every number means e.g. cello1
     * guitarX where x {1-6] check below what every number means e.g. guitar6
     */
    void setOrganSetter(QString setter);

    /**
     * @brief getOrganSetter is a function that returns the organ setter
     * @return the organ setter
     */
    QString getOrganSetter();

    /**
     * @brief getBaseFrequency is a function that returns the base frequency
     * @return the base frequency
     */
    quint16 getBaseFrequency();

    /**
     * @brief setBaseFrequency is a function that changes the base frequency
     * @param frequency is the base frequency value that we want to set
     */
    void setBaseFrequency(quint16 frequency);

    /**
     * @brief getClosestNote is a function that returns the closest note
     * @return the closest note
     */
    QString getClosestNote();

    /**
     * @brief getPercentageOfDistanceFromTheClosestNote is a function that returns the percentage of distance from the closest note
     * @return the percentage of distance from the closest note
     */
    qreal getPercentageOfDistanceFromTheClosestNote();

    /**
     * @brief getFrequency this function returns the frequency
     * @return the frequency
     */
    qreal getFrequency();

signals:
	void samplesAnalyzed();

    void activeChanged();

    void baseFrequencyChanged();

    void organSetterChanged();

private:
    /**
     * @brief applyFormat is a functions that sets the format settings of the audioinput
     */
    void applyFormat();

    /**
     * @brief setCloseNoteAndPercentageAccordingToSetterID this functions sets variable that the front need according to setted id
     */
    void setCloseNoteAndPercentageAccordingToSetterID();

    /**
     * @brief setCello1String is a function that sets the variables for the x string
     * 1 is the string with the highest pitch and 4 is the string with the lowest pitch
     * String: 1 = A3, 2 = D3, 3 = G2, 4 = C2
     * @param x is the number of the string
     */
    void setCelloXString(quint16 x);

    /**
     * @brief setGuitarXString is a function that sets the variables x string.
     * 1 is the string with the highest pitch and 6 is the string with the lowest pitch
     * String: 1 = E4, 2 = B3, 3 = G3, 4 = D3, 5 = A, 6 = E2
     * @param x is the number of the string
     */
    void setGuitarXString(quint16 x);

    /**
     * @brief setFreeMode is a function that sets the variables for the input note
     */
    void setFreeMode();


    /**
     * @brief setTheVariables is a function that sets percentageOfDistanceFromTheClosestNote
     * @param i is the pointer of the closest note
     */
    void setPercentageOfDistanceFromTheClosestNote(quint16 i);

    //  the audioinput device
    std::unique_ptr<QAudioInput> recorder;

    //  the format settings of the qiodevice
    QAudioFormat formatSettings;

    //  the buffer that includes the audio input
    PitchBuffer pitchBuffer;

    //  we use this notes' controller to handle the notes as name and frequencies and their base frequency
    NotesController notesController;

    //  the aubio object
    AubioWrapper aubio;

    //  this variable indicates if the tuner is active or not
    bool activeTuner;

    //  this varibles is the setter id
    QString organSetter;

    //  this variable is used for graphical reasons and it's range is -100 to 100
    qreal percentageOfDistanceFromTheClosestNote;

    //  this variable is used for graphical reasons
    QString closestNote;

    //  this variable stores the last confident current frequency that has recognized
    qreal lastConfidentFrequency;

    //  this variable stores the current frequency that has been recognized
    qreal currentFrequency;

    //  this variable stores the threads hold of the confidence
    float confidenceThresHold = .92;

private slots:
	void analyzeSamples();
};

#endif // Configurator_HPP
