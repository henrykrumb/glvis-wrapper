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
	BB_DASHED,
	
	BB_LAST_ITEM
} BBType;

// background (black/white, key g)
typedef enum {
	BG_WHITE,
	BG_BLACK,
	
	BG_LAST_ITEM
} BGType;

// mesh modes (key m)
typedef enum {
	MESH_NONE,
	MESH_ELEMENT_EDGES,
	MESH_LEVEL_LINES,
	
	MESH_LAST_ITEM
} MeshMode;

// color palettes (key p/P, F6 for overview, default is vivid)
typedef enum {
	PALETTE_5_COLOR,
	PALETTE_RED,
	PALETTE_JET_LIKE,
	PALETTE_COLDHOT,
	PALETTE_BONE,
	PALETTE_HOT,
	PALETTE_PINK,
	PALETTE_COOL,
	PALETTE_SUMMER,
	PALETTE_HSV,
	PALETTE_COPPER,
	PALETTE_WHITE,
	PALETTE_VIVID, // default
	PALETTE_ALUMINUM,
	PALETTE_SUNRISE,
	PALETTE_HORIZON,
	PALETTE_BYR,
	PALETTE_DEEP_SEA,
	PALETTE_PASTEL,
	PALETTE_TROPICAL,
	PALETTE_WOOD,
	PALETTE_MARS,
	PALETTE_RAINBOW,
	PALETTE_CMYK,
	PALETTE_CALEWHITE,
	PALETTE_HAXBY,
	PALETTE_MANGA,
	PALETTE_DRYWET,
	PALETTE_GFDL,
	PALETTE_WBGYR,
	PALETTE_SEQ25,
	PALETTE_TERRAIN,
	PALETTE_BWOR,
	PALETTE_19_LEV,
	PALETTE_LITHOLOGY,
	
	PALETTE_LAST_ITEM
} PaletteType;



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
	void set_palette(PaletteType palette);

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
	PaletteType m_palette;
};
