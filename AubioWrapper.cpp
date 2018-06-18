#include <AubioWrapper.hpp>

AubioWrapper::AubioWrapper() {
	reloadAubio();
    aubioIn = new_fvec(hopSize);
	aubioOut = new_fvec(1);
}

AubioWrapper::~AubioWrapper() {
	del_fvec(aubioIn);
	del_fvec(aubioOut);
}

void AubioWrapper::reloadAubio() {
    aubioPitch = decltype(aubioPitch)(constructAubioPitch(algorithm, bufSize, hopSize, sampleRate), AubioPitchDeleter());
}

aubio_pitch_t *AubioWrapper::getAubioPitch() {
    return aubioPitch.get();
}

aubio_pitch_t *AubioWrapper::constructAubioPitch(QString method, uint_t buf_size, uint_t hop_size, uint_t samplerate) {
	return new_aubio_pitch(method.toLatin1().data(), buf_size, hop_size, samplerate);
}
