#include "Post_processing.h"

Post_processing::Post_processing()
{
	float quadVertices[] = {
	   // positions   // uvs
	   -1.0f,  1.0f,  0.0f, 1.0f,
	   -1.0f, -1.0f,  0.0f, 0.0f,
		1.0f, -1.0f,  1.0f, 0.0f,

	   -1.0f,  1.0f,  0.0f, 1.0f,
		1.0f, -1.0f,  1.0f, 0.0f,
		1.0f,  1.0f,  1.0f, 1.0f
	};

	glGenVertexArrays(1, &quadVAO);
	glBindVertexArray(quadVAO);

	glGenBuffers(1, &quadVBO);
	glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
	
	//vertices
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);

	//uvs
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

	mat = new Material("post_process.vs", "post_process.ps");
	effects = new Effects;
	renderop = new RenderOptions;
	textureLoader = new TextureLoader;
	FBOPostProcessMap = textureLoader->FrameBuffer();
	ProcessMap = textureLoader->RenderTexture(MainSettings::w_window, MainSettings::h_window, 0);
	ProcessMap_1 = textureLoader->RenderTexture(MainSettings::w_window, MainSettings::h_window, 1);
	ProcessMapDepth = textureLoader->RenderDepthTexture(MainSettings::w_window, MainSettings::h_window);
	//textureLoader->RenderBuffer(MainSettings::w_window, MainSettings::h_window);
	unsigned int attachments[2] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1 };
	glDrawBuffers(2, attachments);
	MainLightData::POSTMAP = &ProcessMap;
	MainLightData::POSTMAP_1 = &ProcessMap_1;
	MainLightData::POSTMAP_DEPTH = &ProcessMapDepth;
	MainLightData::FRAMEBUFFERPOST = &FBOPostProcessMap;
	textureLoader->Unbind_FrameBuffer();

	//mat->SetRenderTexture("render", 1300, 950);
	//mat->UnBindRenderTextures();
	Material::Texture tex;
	tex.IdTexture = *MainLightData::POSTMAP;
	tex.Name = "render";
	mat->Textures.push_back(tex);

	Material::Texture tex_1;
	tex_1.IdTexture = *MainLightData::POSTMAP_1;
	tex_1.Name = "bloomBlur";
	mat->Textures.push_back(tex_1);

	Material::Texture tex_2;
	tex_2.IdTexture = *MainLightData::POSTMAP_DEPTH;
	tex_2.Name = "DepthMap";
	mat->Textures.push_back(tex_2);


	effects->Bloom = true;
	effects->Exposure = 0.6f;
	effects->Temperature = true;
	effects->ColorTemperature = 0.023f;
	effects->Saturation = true;
	effects->SaturationValue = 1.373f;
	effects->Vignette = true;
	effects->Vignette_Radio = 0.565f;
	effects->Vignette_Smooth = 0.278f;
}

void Post_processing::GetRender()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	textureLoader->Bind_FrameBuffer(FBOPostProcessMap);
}

void Post_processing::SetRender(Render* render, Scene_Manager* scene)
{
	//mat->UnBindRenderTextures();
	//render->Draw(scene->GetActiveScene());
	//glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//textureLoader->Unbind_FrameBuffer();
	renderop->ZBuffer(false);
	//glViewport(0, 0, MainSettings::w_window, MainSettings::h_window);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//textureLoader->Bind_FrameBuffer(FBOPostProcessMap);

	mat->Draw();
	//Set Effects
	mat->SetInteger("Bloom", effects->Bloom);
	mat->SetFloat("exposure", effects->Exposure);
	mat->SetInteger("Negative", effects->Negative);
	mat->SetInteger("Grayscale", effects->Grayscale);
	mat->SetInteger("Blur", effects->Blur);
	mat->SetInteger("SSAO", effects->SSAO);
	mat->SetInteger("numSamples", effects->NumSamplesSSAO);
	mat->SetFloat("radius", effects->RadiusSSAO);
	mat->SetInteger("Temperature", effects->Temperature);
	mat->SetFloat("colorTemperature", effects->ColorTemperature);
	mat->SetInteger("Saturation", effects->Saturation);
	mat->SetFloat("saturationFactor", effects->SaturationValue);
	mat->SetInteger("Vignette", effects->Vignette);
	mat->SetFloat("smooth_vignette", effects->Vignette_Smooth);
	mat->SetFloat("radio_vignette", effects->Vignette_Radio);

	ImGui::Begin("Post-procesado");
	ImGui::Checkbox("Bloom", &effects->Bloom);
	ImGui::SliderFloat("Exposure", &effects->Exposure, 0.0f, 4.0f);
	ImGui::Checkbox("Negative", &effects->Negative);
	ImGui::Checkbox("Grayscale", &effects->Grayscale);
	ImGui::Checkbox("Blur", &effects->Blur);
	ImGui::Checkbox("SSAO", &effects->SSAO);
	ImGui::SliderFloat("radius", &effects->RadiusSSAO, 0.0f, 1.0f);
	ImGui::Checkbox("Temperature", &effects->Temperature);
	ImGui::SliderFloat("Color Temperature", &effects->ColorTemperature, -1.0f, 1.0f);
	ImGui::Checkbox("Saturation", &effects->Saturation);
	ImGui::SliderFloat("Saturation Value", &effects->SaturationValue, -3.0f, 3.0f);
	ImGui::Checkbox("Vignette", &effects->Vignette);
	ImGui::SliderFloat("Vignette Radio", &effects->Vignette_Radio, 0.0f, 1.0f);
	ImGui::SliderFloat("Vignette Smooth", &effects->Vignette_Smooth, 0.0f, 1.0f);
	ImGui::End();

	glBindVertexArray(quadVAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);

	renderop->ZBuffer(true);
	//textureLoader->Unbind_FrameBuffer();

	//mat->UnBindRenderTextures();
	//render->Update(scene->GetActiveScene());
}