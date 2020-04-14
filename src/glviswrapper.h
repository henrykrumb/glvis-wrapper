/*
 * glviswrapper.h
 * 
 * Provides an OO abstraction to GLVis.
 * Usually, GLVis is controlled by typing key commands in a GLVis window
 * or by sending key commands via socket. The problem is that those key
 * bindings are hard to memorize.
 * 
 * For raw key bindings, see:
 * https://raw.githubusercontent.com/glvis/glvis/master/README
 */
#pragma once
#include <memory>

#include <mfem.hpp>


#define GLVIS_HOST "localhost"
#define GLVIS_PORT 19916


// bounding box types (key a)
typedef enum {
	BB_NONE,
	BB_COORDS,
	BB_NOCOORDS,
	BB_DASHED
} BBType;

// background (black/white, key g)
typedef enum {
	BG_WHITE,
	BG_BLACK
} BGType;

// mesh modes (key m)
typedef enum {
	MESH_NONE,
	MESH_ELEMENT_EDGES,
	MESH_LEVEL_LINES
} MeshMode;



class GLVisWrapper {
public:
	GLVisWrapper(
		const char* host=GLVIS_HOST,
		int port=GLVIS_PORT
	);
	GLVisWrapper(const GLVisWrapper& viz);
	virtual ~GLVisWrapper() = default;

	/*
	 * There is no guarantee that this class is complete. You can use this
	 * method to send your own keys to the socket.
	 */
	void add_key(char key);
	
	void set_antialiasing(bool antialiasing);
	void set_background(BGType bg);
	void set_boundingbox(BBType boundingbox);
	void set_colorbar(bool colorbar);
	void set_light(bool light);
	void set_meshmode(MeshMode meshmode);

	void visualize(
		const mfem::Mesh& mesh,
		const mfem::GridFunction& gf,
		const std::string& title=""
	);

protected:
	const char* m_host;
	int m_port;
	mfem::socketstream m_sock;
	
	std::string m_keys;
	
	bool m_antialiasing;
	BGType m_background;
	BBType m_boundingbox;
	bool m_colorbar;
	bool m_light;
	MeshMode m_meshmode;
};
