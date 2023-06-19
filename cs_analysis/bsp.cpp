#include <iostream>
#include <fstream>
#include <stdint.h>



#define LUMP_ENTITIES      0
#define LUMP_PLANES        1
#define LUMP_TEXTURES      2
#define LUMP_VERTICES      3
#define LUMP_VISIBILITY    4
#define LUMP_NODES         5
#define LUMP_TEXINFO       6
#define LUMP_FACES         7
#define LUMP_LIGHTING      8
#define LUMP_CLIPNODES     9
#define LUMP_LEAVES       10
#define LUMP_MARKSURFACES 11
#define LUMP_EDGES        12
#define LUMP_SURFEDGES    13
#define LUMP_MODELS       14
#define HEADER_LUMPS      15
#define MAX_MAP_HULLS 4

typedef struct _BSPLUMP
{
    int32_t nOffset; // File offset to data
    int32_t nLength; // Length of data
} BSPLUMP;

typedef struct _BSPHEADER
{
    int32_t nVersion;           // Must be 30 for a valid HL BSP file
    BSPLUMP lump[HEADER_LUMPS]; // Stores the directory of lumps
} BSPHEADER;

typedef struct _VECTOR3D
{
    float x, y, z;
} VECTOR3D;

typedef struct _BSPMODEL
{
    float nMins[3], nMaxs[3];          // Defines bounding box
    VECTOR3D vOrigin;                  // Coordinates to move the // coordinate system
    int32_t iHeadnodes[MAX_MAP_HULLS]; // Index into nodes array
    int32_t nVisLeafs;                 // ???
    int32_t iFirstFace, nFaces;        // Index and count into faces
} BSPMODEL;

void* readFile( std::string name, size_t &size ){

    std::ifstream fin( name, std::ios::in | std::ios::binary );

    if ( fin.is_open() ){
        fin.seekg( 0, std::ios::end );
        size = fin.tellg();
        fin.seekg( 0, std::ios::beg );
        void *data = malloc(size);
        fin.read( static_cast<char*>(data), size );
        fin.close();
        return data;
    }

    return NULL;
}

int main(){

    size_t size;
    void* data = readFile( "legoland.bsp", size );
    std::cout << "BSP size:" << size << std::endl;

    BSPHEADER *header = static_cast<BSPHEADER*>(data);
    std::cout << "BSP version:" << header->nVersion << std::endl;

    size_t models = header->lump[LUMP_MODELS].nOffset;

    char *model = static_cast<char*>(data) + models;
    std::cout << model << std::endl;
    std::cout << header->lump[LUMP_MODELS].nLength << std::endl;
    ///std::cout << static_cast<char*>(data) << std::endl;

}