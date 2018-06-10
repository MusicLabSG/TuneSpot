/*
 * File:    Configurator.cpp
 * Author:  Spiros
 *
 * Created on Jun 10, 2018, 5:28 PM
 */

#include "Configurator.h"

Configurator::Configurator() {
    currentFrequency = 0;
    percentageOfDistanceFromTheClosestNote = 0;
    closestNote = "";
    readBaseFrequency();
    readNotes();
}

Configurator::~Configurator() {
    currentFrequency = 0;
    percentageOfDistanceFromTheClosestNote = 0;
    closestNote = "";
}

//  cello functions

void Configurator::setCello1String() {
    closestNote = "A3";
}

void Configurator::setCello2String() {
    closestNote = "D3";
}

void Configurator::Configurator::setCello3String() {
    closestNote = "G2";
}

void Configurator::setCello4String() {
    closestNote = "C2";
}

//  guitar functions

void Configurator::setGuitar1String() {
    closestNote = "E4";
}

void Configurator::setGuitar2String() {
    closestNote = "B3";
}

void Configurator::setGuitar3String() {
    closestNote = "G3";
}

void Configurator::setGuitar4String() {
    closestNote = "D3";
}

void Configurator::setGuitar5String() {
    closestNote = "A2";
}

void Configurator::setGuitar6String() {
    closestNote = "E2";
}

void Configurator::setFreeMode() {

}

quint16 Configurator::getBaseFrequency() {

}

void Configurator::changeBaseFrequency(quint16 frequency) {

}

QString Configurator::getClosestNote() {

}

quint16 Configurator::getPercentageOfDistanceFromTheClosestNote() {

}

void Configurator::readBaseFrequency() {

}

void Configurator::readNotes() {

}

QString Configurator::findClosestNote() {

}

void Configurator::setCurrentFrequency() {

}
