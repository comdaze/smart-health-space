/* Generated by the protocol buffer compiler.  DO NOT EDIT! */
/* Generated from: google/cloud/dialogflow/v2beta1/audio_config.proto */

#ifndef PROTOBUF_C_google_2fcloud_2fdialogflow_2fv2beta1_2faudio_5fconfig_2eproto__INCLUDED
#define PROTOBUF_C_google_2fcloud_2fdialogflow_2fv2beta1_2faudio_5fconfig_2eproto__INCLUDED

#include <protobuf-c/protobuf-c.h>

PROTOBUF_C__BEGIN_DECLS

#if PROTOBUF_C_VERSION_NUMBER < 1003000
# error This file was generated by a newer version of protoc-c which is incompatible with your libprotobuf-c headers. Please update your headers.
#elif 1003000 < PROTOBUF_C_MIN_COMPILER_VERSION
# error This file was generated by an older version of protoc-c which is incompatible with your libprotobuf-c headers. Please regenerate this file with a newer version of protoc-c.
#endif

#include "annotations.pb-c.h"

typedef struct _Google__Cloud__Dialogflow__V2beta1__VoiceSelectionParams Google__Cloud__Dialogflow__V2beta1__VoiceSelectionParams;
typedef struct _Google__Cloud__Dialogflow__V2beta1__SynthesizeSpeechConfig Google__Cloud__Dialogflow__V2beta1__SynthesizeSpeechConfig;
typedef struct _Google__Cloud__Dialogflow__V2beta1__OutputAudioConfig Google__Cloud__Dialogflow__V2beta1__OutputAudioConfig;


/* --- enums --- */

/*
 * Gender of the voice as described in
 * [SSML voice element](https://www.w3.org/TR/speech-synthesis11/#edef_voice).
 */
typedef enum _Google__Cloud__Dialogflow__V2beta1__SsmlVoiceGender {
  /*
   * An unspecified gender, which means that the client doesn't care which
   * gender the selected voice will have.
   */
  GOOGLE__CLOUD__DIALOGFLOW__V2BETA1__SSML_VOICE_GENDER__SSML_VOICE_GENDER_UNSPECIFIED = 0,
  /*
   * A male voice.
   */
  GOOGLE__CLOUD__DIALOGFLOW__V2BETA1__SSML_VOICE_GENDER__SSML_VOICE_GENDER_MALE = 1,
  /*
   * A female voice.
   */
  GOOGLE__CLOUD__DIALOGFLOW__V2BETA1__SSML_VOICE_GENDER__SSML_VOICE_GENDER_FEMALE = 2,
  /*
   * A gender-neutral voice.
   */
  GOOGLE__CLOUD__DIALOGFLOW__V2BETA1__SSML_VOICE_GENDER__SSML_VOICE_GENDER_NEUTRAL = 3
    PROTOBUF_C__FORCE_ENUM_TO_BE_INT_SIZE(GOOGLE__CLOUD__DIALOGFLOW__V2BETA1__SSML_VOICE_GENDER)
} Google__Cloud__Dialogflow__V2beta1__SsmlVoiceGender;
/*
 * Audio encoding of the output audio format in Text-To-Speech.
 */
typedef enum _Google__Cloud__Dialogflow__V2beta1__OutputAudioEncoding {
  /*
   * Not specified.
   */
  GOOGLE__CLOUD__DIALOGFLOW__V2BETA1__OUTPUT_AUDIO_ENCODING__OUTPUT_AUDIO_ENCODING_UNSPECIFIED = 0,
  /*
   * Uncompressed 16-bit signed little-endian samples (Linear PCM).
   * Audio content returned as LINEAR16 also contains a WAV header.
   */
  GOOGLE__CLOUD__DIALOGFLOW__V2BETA1__OUTPUT_AUDIO_ENCODING__OUTPUT_AUDIO_ENCODING_LINEAR_16 = 1,
  /*
   * MP3 audio.
   */
  GOOGLE__CLOUD__DIALOGFLOW__V2BETA1__OUTPUT_AUDIO_ENCODING__OUTPUT_AUDIO_ENCODING_MP3 = 2,
  /*
   * Opus encoded audio wrapped in an ogg container. The result will be a
   * file which can be played natively on Android, and in browsers (at least
   * Chrome and Firefox). The quality of the encoding is considerably higher
   * than MP3 while using approximately the same bitrate.
   */
  GOOGLE__CLOUD__DIALOGFLOW__V2BETA1__OUTPUT_AUDIO_ENCODING__OUTPUT_AUDIO_ENCODING_OGG_OPUS = 3
    PROTOBUF_C__FORCE_ENUM_TO_BE_INT_SIZE(GOOGLE__CLOUD__DIALOGFLOW__V2BETA1__OUTPUT_AUDIO_ENCODING)
} Google__Cloud__Dialogflow__V2beta1__OutputAudioEncoding;

/* --- messages --- */

/*
 * Description of which voice to use for speech synthesis.
 */
struct  _Google__Cloud__Dialogflow__V2beta1__VoiceSelectionParams
{
  ProtobufCMessage base;
  /*
   * Optional. The name of the voice. If not set, the service will choose a
   * voice based on the other parameters such as language_code and gender.
   */
  char *name;
  /*
   * Optional. The preferred gender of the voice. If not set, the service will
   * choose a voice based on the other parameters such as language_code and
   * name. Note that this is only a preference, not requirement. If a
   * voice of the appropriate gender is not available, the synthesizer should
   * substitute a voice with a different gender rather than failing the request.
   */
  Google__Cloud__Dialogflow__V2beta1__SsmlVoiceGender ssml_gender;
};
#define GOOGLE__CLOUD__DIALOGFLOW__V2BETA1__VOICE_SELECTION_PARAMS__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&google__cloud__dialogflow__v2beta1__voice_selection_params__descriptor) \
    , (char *)protobuf_c_empty_string, GOOGLE__CLOUD__DIALOGFLOW__V2BETA1__SSML_VOICE_GENDER__SSML_VOICE_GENDER_UNSPECIFIED }


/*
 * Configuration of how speech should be synthesized.
 */
struct  _Google__Cloud__Dialogflow__V2beta1__SynthesizeSpeechConfig
{
  ProtobufCMessage base;
  /*
   * Optional. Speaking rate/speed, in the range [0.25, 4.0]. 1.0 is the normal
   * native speed supported by the specific voice. 2.0 is twice as fast, and
   * 0.5 is half as fast. If unset(0.0), defaults to the native 1.0 speed. Any
   * other values < 0.25 or > 4.0 will return an error.
   */
  double speaking_rate;
  /*
   * Optional. Speaking pitch, in the range [-20.0, 20.0]. 20 means increase 20
   * semitones from the original pitch. -20 means decrease 20 semitones from the
   * original pitch.
   */
  double pitch;
  /*
   * Optional. Volume gain (in dB) of the normal native volume supported by the
   * specific voice, in the range [-96.0, 16.0]. If unset, or set to a value of
   * 0.0 (dB), will play at normal native signal amplitude. A value of -6.0 (dB)
   * will play at approximately half the amplitude of the normal native signal
   * amplitude. A value of +6.0 (dB) will play at approximately twice the
   * amplitude of the normal native signal amplitude. We strongly recommend not
   * to exceed +10 (dB) as there's usually no effective increase in loudness for
   * any value greater than that.
   */
  double volume_gain_db;
  /*
   * Optional. An identifier which selects 'audio effects' profiles that are
   * applied on (post synthesized) text to speech. Effects are applied on top of
   * each other in the order they are given.
   */
  size_t n_effects_profile_id;
  char **effects_profile_id;
  /*
   * Optional. The desired voice of the synthesized audio.
   */
  Google__Cloud__Dialogflow__V2beta1__VoiceSelectionParams *voice;
};
#define GOOGLE__CLOUD__DIALOGFLOW__V2BETA1__SYNTHESIZE_SPEECH_CONFIG__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&google__cloud__dialogflow__v2beta1__synthesize_speech_config__descriptor) \
    , 0, 0, 0, 0,NULL, NULL }


/*
 * Instructs the speech synthesizer how to generate the output audio content.
 */
struct  _Google__Cloud__Dialogflow__V2beta1__OutputAudioConfig
{
  ProtobufCMessage base;
  /*
   * Required. Audio encoding of the synthesized audio content.
   */
  Google__Cloud__Dialogflow__V2beta1__OutputAudioEncoding audio_encoding;
  /*
   * Optional. The synthesis sample rate (in hertz) for this audio. If not
   * provided, then the synthesizer will use the default sample rate based on
   * the audio encoding. If this is different from the voice's natural sample
   * rate, then the synthesizer will honor this request by converting to the
   * desired sample rate (which might result in worse audio quality).
   */
  int32_t sample_rate_hertz;
  /*
   * Optional. Configuration of how speech should be synthesized.
   */
  Google__Cloud__Dialogflow__V2beta1__SynthesizeSpeechConfig *synthesize_speech_config;
};
#define GOOGLE__CLOUD__DIALOGFLOW__V2BETA1__OUTPUT_AUDIO_CONFIG__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&google__cloud__dialogflow__v2beta1__output_audio_config__descriptor) \
    , GOOGLE__CLOUD__DIALOGFLOW__V2BETA1__OUTPUT_AUDIO_ENCODING__OUTPUT_AUDIO_ENCODING_UNSPECIFIED, 0, NULL }


/* Google__Cloud__Dialogflow__V2beta1__VoiceSelectionParams methods */
void   google__cloud__dialogflow__v2beta1__voice_selection_params__init
                     (Google__Cloud__Dialogflow__V2beta1__VoiceSelectionParams         *message);
size_t google__cloud__dialogflow__v2beta1__voice_selection_params__get_packed_size
                     (const Google__Cloud__Dialogflow__V2beta1__VoiceSelectionParams   *message);
size_t google__cloud__dialogflow__v2beta1__voice_selection_params__pack
                     (const Google__Cloud__Dialogflow__V2beta1__VoiceSelectionParams   *message,
                      uint8_t             *out);
size_t google__cloud__dialogflow__v2beta1__voice_selection_params__pack_to_buffer
                     (const Google__Cloud__Dialogflow__V2beta1__VoiceSelectionParams   *message,
                      ProtobufCBuffer     *buffer);
Google__Cloud__Dialogflow__V2beta1__VoiceSelectionParams *
       google__cloud__dialogflow__v2beta1__voice_selection_params__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   google__cloud__dialogflow__v2beta1__voice_selection_params__free_unpacked
                     (Google__Cloud__Dialogflow__V2beta1__VoiceSelectionParams *message,
                      ProtobufCAllocator *allocator);
/* Google__Cloud__Dialogflow__V2beta1__SynthesizeSpeechConfig methods */
void   google__cloud__dialogflow__v2beta1__synthesize_speech_config__init
                     (Google__Cloud__Dialogflow__V2beta1__SynthesizeSpeechConfig         *message);
size_t google__cloud__dialogflow__v2beta1__synthesize_speech_config__get_packed_size
                     (const Google__Cloud__Dialogflow__V2beta1__SynthesizeSpeechConfig   *message);
size_t google__cloud__dialogflow__v2beta1__synthesize_speech_config__pack
                     (const Google__Cloud__Dialogflow__V2beta1__SynthesizeSpeechConfig   *message,
                      uint8_t             *out);
size_t google__cloud__dialogflow__v2beta1__synthesize_speech_config__pack_to_buffer
                     (const Google__Cloud__Dialogflow__V2beta1__SynthesizeSpeechConfig   *message,
                      ProtobufCBuffer     *buffer);
Google__Cloud__Dialogflow__V2beta1__SynthesizeSpeechConfig *
       google__cloud__dialogflow__v2beta1__synthesize_speech_config__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   google__cloud__dialogflow__v2beta1__synthesize_speech_config__free_unpacked
                     (Google__Cloud__Dialogflow__V2beta1__SynthesizeSpeechConfig *message,
                      ProtobufCAllocator *allocator);
/* Google__Cloud__Dialogflow__V2beta1__OutputAudioConfig methods */
void   google__cloud__dialogflow__v2beta1__output_audio_config__init
                     (Google__Cloud__Dialogflow__V2beta1__OutputAudioConfig         *message);
size_t google__cloud__dialogflow__v2beta1__output_audio_config__get_packed_size
                     (const Google__Cloud__Dialogflow__V2beta1__OutputAudioConfig   *message);
size_t google__cloud__dialogflow__v2beta1__output_audio_config__pack
                     (const Google__Cloud__Dialogflow__V2beta1__OutputAudioConfig   *message,
                      uint8_t             *out);
size_t google__cloud__dialogflow__v2beta1__output_audio_config__pack_to_buffer
                     (const Google__Cloud__Dialogflow__V2beta1__OutputAudioConfig   *message,
                      ProtobufCBuffer     *buffer);
Google__Cloud__Dialogflow__V2beta1__OutputAudioConfig *
       google__cloud__dialogflow__v2beta1__output_audio_config__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   google__cloud__dialogflow__v2beta1__output_audio_config__free_unpacked
                     (Google__Cloud__Dialogflow__V2beta1__OutputAudioConfig *message,
                      ProtobufCAllocator *allocator);
/* --- per-message closures --- */

typedef void (*Google__Cloud__Dialogflow__V2beta1__VoiceSelectionParams_Closure)
                 (const Google__Cloud__Dialogflow__V2beta1__VoiceSelectionParams *message,
                  void *closure_data);
typedef void (*Google__Cloud__Dialogflow__V2beta1__SynthesizeSpeechConfig_Closure)
                 (const Google__Cloud__Dialogflow__V2beta1__SynthesizeSpeechConfig *message,
                  void *closure_data);
typedef void (*Google__Cloud__Dialogflow__V2beta1__OutputAudioConfig_Closure)
                 (const Google__Cloud__Dialogflow__V2beta1__OutputAudioConfig *message,
                  void *closure_data);

/* --- services --- */


/* --- descriptors --- */

extern const ProtobufCEnumDescriptor    google__cloud__dialogflow__v2beta1__ssml_voice_gender__descriptor;
extern const ProtobufCEnumDescriptor    google__cloud__dialogflow__v2beta1__output_audio_encoding__descriptor;
extern const ProtobufCMessageDescriptor google__cloud__dialogflow__v2beta1__voice_selection_params__descriptor;
extern const ProtobufCMessageDescriptor google__cloud__dialogflow__v2beta1__synthesize_speech_config__descriptor;
extern const ProtobufCMessageDescriptor google__cloud__dialogflow__v2beta1__output_audio_config__descriptor;

PROTOBUF_C__END_DECLS


#endif  /* PROTOBUF_C_google_2fcloud_2fdialogflow_2fv2beta1_2faudio_5fconfig_2eproto__INCLUDED */
