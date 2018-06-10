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

void Configurator::setCelloXString(quint16 x) {
    if (x == 1) {
        closestNote == "A3";
    } else if (x == 2) {
        closestNote == "D3";
    } else if (x == 3) {
        closestNote == "G2";
    } else if (x == 4) {
        closestNote == "C2";
    }
}

void Configurator::setGuitarXString(quint16 x) {
    if (x == 1) {
        closestNote == "E4";
    } else if (x == 2) {
        closestNote == "B3";
    } else if (x == 3) {
        closestNote == "G3";
    } else if (x == 4) {
        closestNote == "D3";
    } else if (x == 5) {
        closestNote == "A2";
    } else if (x == 6) {
        closestNote == "E2";
    }
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
