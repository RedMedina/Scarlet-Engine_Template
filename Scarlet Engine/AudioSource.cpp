#include "AudioSource.h"

AudioSource::AudioSource(const char* soundpath, glm::vec3 Position, bool is3D)
{
	FMOD_RESULT result = FMOD::System_Create(&m_system);
	if (result != FMOD_OK)
		std::cerr << "Error al crear el sistema de sonido FMOD\n";

	result = m_system->init(512, FMOD_INIT_NORMAL, nullptr);
	if (result != FMOD_OK)
		std::cerr << "Error al inicializar el sistema de sonido FMOD\n";

	result = m_system->createSound(soundpath, FMOD_DEFAULT, 0, &m_sound);
	if (result != FMOD_OK)
		std::cerr << "Error al cargar el sonido: " << soundpath << std::endl;

	if (is3D)
	{
		m_sound->set3DMinMaxDistance(1.0f, 10000.0f);
	}
	is3DSound = is3D;
}

void AudioSource::Draw() 
{
	if (MainSettings::RenderN == MainSettings::NumRenders)
	{
		if (ImGui::Button(PlayBTN ? "Pause" : "Play")) {
			if (PlayBTN) {
				pause();
			}
			else {
				play();
			}
			PlayBTN = !PlayBTN;
		}

		if (ImGui::Button(LoopBTN ? "Loop: No" : "Loop: Yes")) {
			if (LoopBTN) {
				SetLoop();
			}
			else {
				NoLoop();
			}
			LoopBTN = !LoopBTN;
		}

		ImGui::SliderFloat("Volume", &volumeF, 0.0f, 2.0f);
		ImGui::SliderFloat("Speed", &speedF, 0.0f, 1.0f);
	}

	setVolume(volumeF);
	SetMusicSpeed(speedF);
}

void AudioSource::Update() {}

void AudioSource::SetLoop()
{
	m_sound->setMode(FMOD_LOOP_NORMAL);
}

void AudioSource::NoLoop()
{
	m_sound->setMode(FMOD_DEFAULT);
}

void AudioSource::SetMusicSpeed(float speed)
{
	m_sound->setMusicSpeed(speed);
}

AudioSource::~AudioSource() {
	m_sound->release();
	m_system->close();
	m_system->release();
}

void AudioSource::play()
{
	m_system->playSound(m_sound, nullptr, false, &m_channel);
}

void AudioSource::pause()
{
	bool paused;
	m_channel->getPaused(&paused);
	m_channel->setPaused(!paused);
}

void AudioSource::stop()
{
	m_channel->stop();
}

void AudioSource::setVolume(float volume)
{
	m_channel->setVolume(volume);
}