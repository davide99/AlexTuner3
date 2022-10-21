#ifndef AUDIOANALYZER_H
#define AUDIOANALYZER_H

#include "CircularBuffer.h"
#include <memory>
#include <fftw3.h>

class AudioAnalyzer {
private:
    CircularBuffer<std::int16_t> buffer;
    std::unique_ptr<float[]> window;
    std::unique_ptr<float[]> fft_input;
    fftwf_plan fft_plan;
    std::unique_ptr<fftwf_complex[]> fft_out;
    std::unique_ptr<float[]> fft_out_magnitude;
    float freq;


public:
    AudioAnalyzer();
    ~AudioAnalyzer();

    void feed_data(short *data, int length);

    float compute_freq();

    static int get_sample_rate();

    static int get_chunk_size();
};

#endif //AUDIOANALYZER_H