/*
 * File:    AubioWrapper.hpp
 * Author:  Theodor
 *
 * Created on Jun 14, 2018, 5:29 PM
 */

#ifndef AUBIOWRAPPER_H
#define AUBIOWRAPPER_H

#include <PitchBuffer.hpp>
#include <bits/unique_ptr.h>

class AubioWrapper
{
public:
	AubioWrapper();

	~AubioWrapper();

    /**
     * @brief setSampleRate is a function that sets the sample rate
     * @param sampleRate is that value selected for the sample rate
     */
    void setSampleRate(const uint_t sampleRate);

    /**
     * @brief getAubioPitch is function that returns the aubio_pitch_t object
     * @return the aubio_pitch_t object
     */
	aubio_pitch_t *getAubioPitch();

    //  this variable defines the sample input
	fvec_t *aubioIn;

    //  this variable defines the sample output after the recognisition of the of the pitch
    fvec_t *aubioOut;

private:
	struct AubioPitchDeleter {
        void operator() (aubio_pitch_t *a) {
            del_aubio_pitch(a);
        }
	};

    /**
     * @brief reloadAubio is a function that reloads the settings of the aubio library
     */
    void reloadAubio();

    /**
     * @brief constructAubioPitch is a function that defines the settings of the aubio library
     * @param method is the algorithm that we use in order recognise the frequency
     * @param buf_size is the buffer size
     * @param hop_size is the hop size
     * @param samplerate is the sample rate
     * @return the aubio_pitch_t object
     */
	aubio_pitch_t *constructAubioPitch(QString method, uint_t buf_size, uint_t hop_size, uint_t samplerate);

    //  a variable that indicates aubio pitch that is gonna be used for the recognition of the pitch
    std::unique_ptr<aubio_pitch_t, AubioPitchDeleter> aubioPitch;

	//	the algorithm that we use in order recognise the frequency
    QString algorithm = "yinfft";

    //	the buffer size
    uint_t bufSize = BUF_SIZE;

    //	the hop size
    uint_t hopSize = HOP_SIZE;

    //	the sample rate
    uint_t sampleRate = 48000;
};

#endif // AUBIOWRAPPER_H
