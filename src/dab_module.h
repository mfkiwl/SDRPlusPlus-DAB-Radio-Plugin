#pragma once

#include <complex>
#include <string>

#include <core.h>
#include <module.h>
#include <config.h>
#include <signal_path/vfo_manager.h>
#include <signal_path/sink.h>
#include <dsp/sink.h>
#include <dsp/stream.h>
#include <dsp/resampling.h>

#include "audio/frame.h"
#include "utility/span.h"

extern ConfigManager config;

class DAB_Decoder;
class AudioPlayer;
class DAB_Decoder_ImGui;

class DAB_Decoder_Sink: public dsp::HandlerSink<dsp::complex_t>
{
private:
    using base_type = dsp::HandlerSink<dsp::complex_t>;
    std::shared_ptr<DAB_Decoder> decoder;
public:
    DAB_Decoder_Sink(std::shared_ptr<DAB_Decoder> _decoder); 
    ~DAB_Decoder_Sink(); 
    void Process(const std::complex<float>* x, const int N);
public:
    auto& GetDecoder() { return *(decoder.get()); }
};

class Audio_Player_Stream
{
private:
    dsp::stream<dsp::stereo_t> output_stream;
public:
    Audio_Player_Stream(AudioPlayer& audio_player);
    ~Audio_Player_Stream();
public:
    auto& GetOutputStream() { return output_stream; }
private:
    void Process(tcb::span<const Frame<float>> rd_buf);
};

class DABModule: public ModuleManager::Instance 
{
private:
    std::shared_ptr<DAB_Decoder> dab_decoder;
    std::unique_ptr<DAB_Decoder_ImGui> dab_decoder_imgui;

    std::string name;
    bool is_enabled;
    std::unique_ptr<DAB_Decoder_Sink> decoder_sink;
    std::unique_ptr<Audio_Player_Stream> audio_player_stream;
    VFOManager::VFO* vfo;
    dsp::filter_window::BlackmanWindow audio_resampler_window;
    dsp::PolyphaseResampler<dsp::stereo_t> audio_resampler;
    SinkManager::Stream audio_stream;
    EventHandler<float> ev_handler_sample_rate_change;
public:
    DABModule(std::string _name); 
    virtual ~DABModule();

    void postInit();
    void enable(); 
    void disable(); 
    bool isEnabled(); 
private:
    void RenderMenu(); 
    void DrawConstellation(tcb::span<const std::complex<float>> data);
    void OnSampleRateChange(float new_sample_rate);
};