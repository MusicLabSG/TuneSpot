/*
 * File:    Configurator.cpp
 * Author:  Spiros
 *
 * Created on Jun 10, 2018, 5:28 PM
 */

#ifndef CONFIGURATOR_H
#define CONFIGURATOR_H

#include <QObject>

class Configurator : public QObject
{
    Q_OBJECT
public:
    explicit Configurator();

    explicit ~Configurator();

public slots:
    //  cello functions

    /**
     * @brief setCello1String is a function that sets the variables for the A3 note
     */
    void setCello1String();

    /**
     * @brief setCello2String is a function that sets the variables for the D3 note
     */
    void setCello2String();

    /**
     * @brief setCello3String is a function that sets the variables for the G2 note
     */
    void setCello3String();

    /**
     * @brief setCello4String is a function that sets the variables for the C2 note
     */
    void setCello4String();

    //  guitar functions

    /**
     * @brief setGuitar1String is a function that sets the variables for the E4 note
     */
    void setGuitar1String();

    /**
     * @brief setGuitar2String is a function that sets the variables for the B3 note
     */
    void setGuitar2String();

    /**
     * @brief setGuitar3String is a function that sets the variables for the G3 note
     */
    void setGuitar3String();

    /**
     * @brief setGuitar4String is a function that sets the variables for the D3 note
     */
    void setGuitar4String();

    /**
     * @brief setGuitar5String is a function that sets the variables for the A2 note
     */
    void setGuitar5String();

    /**
     * @brief setGuitar6String is a function that sets the variables for the E2 note
     */
    void setGuitar6String();

    //  free mode

    /**
     * @brief setFreeMode is a function that sets the variables for the input note
     */
    void setFreeMode();

    // rest functions

    /**
     * @brief getBaseFrequency is a function that returns the base frequency
     * @return the base frequency
     */
    quint16 getBaseFrequency();

    /**
     * @brief changeBaseFrequency is a function that changes the base frequency
     */
    void changeBaseFrequency(quint16 frequency);

    /**
     * @brief getClosestNote is a function that returns the closest note
     * @return the closest note
     */
    QString getClosestNote();

    /**
     * @brief getPercentageOfDistanceFromTheClosestNote is a function that returns the percentage of distance from the closest note
     * @return the percentage of distance from the closest note
     */
    quint16 getPercentageOfDistanceFromTheClosestNote();

private slots:
    /**
     * @brief readBaseFrequency is a functions that reads the base Frequency
     */
    void readBaseFrequency();

    /**
     * @brief readNotes is a function that reads the notes
     */
    void readNotes();

    /**
     * @brief findClosestNote is a functions that find the closest not based on the current frequency
     * @return the closest not based on the current frequency
     */
    QString findClosestNote();

    /**
     * @brief setCurrentFrequency is a function that sets the current frenquency that has been recognized from the test input file
     */
    void setCurrentFrequency();
private:
    //  this variable stores the currunt frequency that has recognized from the test input file
    double currentFrequency;

    //  this variable is used for graphical reasons
    quint16 percentageOfDistanceFromTheClosestNote;

    //  this variable is used for graphical reasons
    QString closestNote;

    // this variable stores the base frequency
    quint16 baseFrequency;

    //  this variable stores the notes with their name and their frequency
    QMap<QString, double> notes;
};

#endif // CONFIGURATOR_H
