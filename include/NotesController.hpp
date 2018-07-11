/*
 * File:    NotesController.cpp
 * Author:  Spiros
 *
 * Created on Jun 10, 2018, 5:28 PM
 */

#ifndef NOTESCONTROLLER_HPP
#define NOTESCONTROLLER_HPP

#include <QObject>
#include <QVector>

class NotesController : public QObject  {
    Q_OBJECT
public:
    explicit NotesController(QObject *parent = nullptr);

    /**
     * @brief changeBaseFrequency is a function the changes the base frequency and the rest frequencies
     * @param newBaseFrequency is the new base base frequency
     */
    void changeBaseFrequency(quint32 newBaseFrequency);

    /**
     * @brief getBaseFrequency is a function that returns the base frequency
     * @return the base frequency
     */
    quint16 getBaseFrequency();

    /**
     * @brief setCloseNoteAndPercentageAccordingToSetterID this functions sets the variables that the front needs according to setted id
     * @param organSetter is the given organ setter
     * @param confidentFrequency is the given confident frequency
     * @param closeNote is the note that we want define
     * @param percentageOfDistanceFromTheClosestNote is the percentage that we want to define
     */
    void setCloseNoteAndPercentageAccordingToSetterID(QString &organSetter, qreal &confidentFrequency, QString &closestNote, qreal &percentageOfDistanceFromTheClosestNote);

private:
    /**
     * @brief setCello1String is a function that sets the variables for the x string
     * 1 is the string with the highest pitch and 4 is the string with the lowest pitch
     * String: 1 = A3, 2 = D3, 3 = G2, 4 = C2
     * @param x is the number of the string
     * @param confidentFrequency is the given confident frequency
     * @param closeNote is the note that we want define
     * @param percentageOfDistanceFromTheClosestNote is the percentage that we want to define
     */
    void setCelloXString(quint16 x, qreal &confidentFrequency, QString &closestNote, qreal &percentageOfDistanceFromTheClosestNote);

    /**
     * @brief setGuitarXString is a function that sets the variables x string.
     * 1 is the string with the highest pitch and 6 is the string with the lowest pitch
     * String: 1 = E4, 2 = B3, 3 = G3, 4 = D3, 5 = A, 6 = E2
     * @param x is the number of the string
     * @param confidentFrequency is the given confident frequency
     * @param closeNote is the note that we want define
     * @param percentageOfDistanceFromTheClosestNote is the percentage that we want to define
     */
    void setGuitarXString(quint16 x, qreal &confidentFrequency, QString &closestNote, qreal &percentageOfDistanceFromTheClosestNote);

    /**
     * @brief setFreeMode is a function that sets the variables for the input note
     * @param confidentFrequency is the given confident frequency
     * @param closeNote is the note that we want define
     * @param percentageOfDistanceFromTheClosestNote is the percentage that we want to define
     */
    void setFreeMode(qreal &confidentFrequency, QString &closestNote, qreal &percentageOfDistanceFromTheClosestNote);

    /**
     * @brief setTheVariables is a function that sets percentageOfDistanceFromTheClosestNote
     * @param i is the pointer of the closest note
     * @param confidentFrequency is the given confident frequency
     * @param percentageOfDistanceFromTheClosestNote is the percentage that we want to define
     */
    void setPercentageOfDistanceFromTheClosestNote(quint16 i, qreal &confidentFrequency, qreal &percentageOfDistanceFromTheClosestNote);

    /**
     * @brief readNotes is a function that reads the notes
     */
    void readNotes();

    //  is the base frequency
    quint16 baseFrequency;

    //  are the names of the notes
    QVector<QString> noteNames;

    //  are the frequencies of the notes
    QVector<qreal> noteFrequencies;

    //  the path for the folder of Tunespot in documents
    QString path;
};

#endif // NOTESCONTROLLER_HPP
