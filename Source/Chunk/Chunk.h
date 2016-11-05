#ifndef CHUNK_H
#define CHUNK_H

#include <unordered_map>
#include <memory>
#include <vector>
#include <array>

#include <SFML/Graphics.hpp>

#include "OpenGL/Glm/glm_transformations.h"
#include "Chunk_Location.h"
#include "Model.h"
#include "Block/Block.h"
#include "Chunk/Chunk_Mesh.h"
#include "Chunk_Layer.h"
#include "Block_Location.h"

class Texture_Atlas;
class World;
class Chunk_Map;

class Chunk;
typedef std::unique_ptr<Chunk> Chunk_Ptr;

class Chunk
{
    public:
        Chunk(const Chunk_Location& position, Chunk_Map& chunkMap, const Texture_Atlas& blockAtlas);

        void generateBlockData ();

        bool hasBlockData   () const;
        bool hasMesh        () const;
        bool hasBuffered    () const;

        void generateMesh   ();
        void bufferMesh     ();

        const Texture_Atlas& getAtlas () const;

        const Block_t& getBlock (const Block_Location& location) const;

        const Chunk_Location& getLocation () const;
        const Vector2&  getPosition () const;

        void setBlock   (const Block_Location& location, Block::Block_Base& block, bool overrideBlocks = true);

        const Model& getChunkModel  () const;
        const Model& getWaterModel  () const;
        const Model& getFloraModel  () const;

        void giveDeleteFlag ();
        bool hasDeleteFlag  () const;

        void update         ();
        void giveUpdateFlag ();
        bool hasUpdateFlag  () const;

        static constexpr int SIZE  = 16,
                             WATER_LEVEL = 115,
                             BEACH_LEVEL = WATER_LEVEL + 2;

    private:
        void generateStructureData  ();

        void makeTree   (const Block_Location& location);

        void qSetBlock  (const Block_Location& location, Block_t& block, bool overrideBlocks = true);

        const Block_t& getAdjChunkBlock (int xChange, int zChange, const Block_Location& location) const;

        void genAdjChunks(const Chunk_Location& location);

        void addLayers (unsigned target);

    private:
        std::vector<Chunk_Layer> m_layers;
        std::vector<Block_Location> m_treeLocations;

        std::map<Block_Location, Block::ID> m_addedBlocks;

        Chunk_Location m_location; //Map coords
        Vector2  m_position; //GL coords

        Chunk_Map* m_p_chunkMap;

        const Texture_Atlas* m_p_atlas;

        bool m_hasBlockData     = false;
        bool m_hasMesh          = false;
        bool m_hasBuffered      = false;

        bool m_hasDeleteFlag    = false;
        bool m_hasUpdateFlag    = false;

        Chunk_Mesh m_mesh;
};


#endif // CHUNK_H
