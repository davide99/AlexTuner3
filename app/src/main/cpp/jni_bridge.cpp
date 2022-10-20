#ifndef MODULE_NAME
#define MODULE_NAME  "jni_bridge"
#endif

#include <jni.h>
#include "AudioAnalyzer.h"

static AudioAnalyzer *audioRecorder = nullptr;

extern "C" JNIEXPORT jboolean JNICALL
Java_com_davide99_alextuner_AudioAnalyzer_init(JNIEnv *env, jclass) {
    if (audioRecorder == nullptr)
        audioRecorder = new AudioAnalyzer();

    return audioRecorder != nullptr;
}

extern "C" JNIEXPORT void JNICALL
Java_com_davide99_alextuner_AudioAnalyzer_destroy(JNIEnv *env, jclass) {
    //seek & destroy
    delete audioRecorder;
    audioRecorder = nullptr;
}

extern "C" JNIEXPORT void JNICALL
Java_com_davide99_alextuner_AudioAnalyzer_feedData(
        JNIEnv *env, jclass, jshortArray data) {

    if (audioRecorder == nullptr)
        return;

    //https://www.iitk.ac.in/esc101/05Aug/tutorial/native1.1/implementing/array.html
    auto array = env->GetShortArrayElements(data, nullptr);
    audioRecorder->feed_data(array, env->GetArrayLength(data));
    env->ReleaseShortArrayElements(data, array, 0);
}

extern "C" JNIEXPORT jfloat JNICALL
Java_com_davide99_alextuner_AudioAnalyzer_computeFreq(JNIEnv *env, jclass) {
    if (audioRecorder == nullptr)
        return 0;

    return audioRecorder->compute_freq();
}