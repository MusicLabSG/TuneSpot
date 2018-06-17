/*
 * File:    Configurator.cpp
 * Author:  Spiros
 *
 * Created on Jun 10, 2018, 5:28 PM
 */

#ifndef CONFIGURATOR_H
#define CONFIGURATOR_H

#include "NotesController.hpp"
#include "Recorder.hpp"
#include <QDebug>
#include <QObject>

class Configurator : public QObject {
    Q_OBJECT
public:
    explicit Configurator();

    ~Configurator();

public slots:
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
     * @brief getBaseFrequency is a function that returns the base frequency
     * @return the base frequency
     */
    quint16 getBaseFrequency();

    /**
     * @brief changeBaseFrequency is a function that changes the base frequency
     * @param frequency is the base frequency value that we want to set
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
    qreal getPercentageOfDistanceFromTheClosestNote();

    /**
     * @brief setCurrentFrequency is a function that sets the current frenquency that has been recognized from the test input file
     */
    void setCurrentFrequency();

    /**
     * @brief analize is a function that analise the a wave file and finds the current frequency
     */
    void analize();

private:
    /**
     * @brief setTheVariables is a function that sets percentageOfDistanceFromTheClosestNote
     * @param i is the pointer of the closest note
     */
    void setPercentageOfDistanceFromTheClosestNote(quint16 i);

    //  we use this recorder to record the test input file
    Recorder *recorder;

    //  we use this notes' controller to handle the notes as name and frequencies and their base frequency
    NotesController *notesController;

    //  this variable stores the currunt frequency that has recognized from the test input file
    qreal currentFrequency;

    //  this variable is used for graphical reasons and it's range is -100 to 100
    qreal percentageOfDistanceFromTheClosestNote;

    //  this variable is used for graphical reasons
    QString closestNote;
};

#endif // CONFIGURATOR_H
