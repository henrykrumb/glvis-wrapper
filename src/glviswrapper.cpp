#include <cmath>
#include <iostream>

#include "glviswrapper.h"


GLVisWrapper::GLVisWrapper(
		const char* host/*=GLVIS_HOST*/,
		int port/*=GLVIS_PORT*/
	):
		m_host(host),
		m_port(port),
		m_sock(host, port),
		m_keys(""),
		m_antialiasing(false),
		m_background(BG_WHITE),
		m_boundingbox(BB_NONE),
		m_colorbar(false),
		m_light(true),
		m_meshmode(MESH_NONE)
{
}


GLVisWrapper::GLVisWrapper(const GLVisWrapper& viz):
		m_sock(viz.m_host, viz.m_port)
{
	// use setters here to get m_keys attribute right
	set_antialiasing(viz.m_antialiasing);
	set_background(viz.m_background);
	set_boundingbox(viz.m_boundingbox);
	set_colorbar(viz.m_colorbar);
	set_light(viz.m_light);
	set_meshmode(viz.m_meshmode);
}


void GLVisWrapper::add_key(char key) {
	m_keys += key;
}


void GLVisWrapper::set_antialiasing(bool antialiasing) {
	if (antialiasing != m_antialiasing) {
		m_keys += "A";
		m_antialiasing = antialiasing;
	}
}


void GLVisWrapper::set_background(BGType background) {
	// 'background' only has two states and can be treated like a boolean
	if (background != m_background) {
		m_keys += "g";
		m_background = background;
	}
}


void GLVisWrapper::set_boundingbox(BBType boundingbox) {
	if (boundingbox != m_boundingbox) {
		int steps = abs(m_boundingbox - boundingbox) % 4;
		for (int i = 0; i < steps; ++i) {
			m_keys += "a";
		}
		m_boundingbox = boundingbox;
	}
}


void GLVisWrapper::set_colorbar(bool colorbar) {
	if (colorbar != m_colorbar) {
		m_keys += "c";
		m_colorbar = colorbar;
	}
}


void GLVisWrapper::set_light(bool light) {
	if (light != m_light) {
		m_keys += "l";
		m_light = light;
	}
}


void GLVisWrapper::set_meshmode(MeshMode meshmode) {
	if (meshmode != m_meshmode) {
		int steps = abs(m_meshmode - meshmode) % 3;
		for (int i = 0; i < steps; ++i) {
			m_keys += "m";
		}
		m_meshmode = meshmode;
	}
}


void GLVisWrapper::visualize(
		const mfem::Mesh& mesh,
		const mfem::GridFunction& gf,
		const std::string& title/*=""*/
	) {
	m_sock.precision(8);
	m_sock << "solution\n" << mesh << gf << std::flush;
	if (!m_keys.empty()) {
		m_sock << "keys " << m_keys << "\n";
		if (!title.empty()) {
			m_sock << "window_title '" << title << "'\n";
		}
	}
	m_keys = "";
}

