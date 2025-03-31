#include "Mesh.hpp"

#include <gmsh.h>

#include <iostream>
#include <fstream>

namespace lin_tetra
{
Mesh::Mesh()
{
    gmsh::initialize();
}

Mesh::EltsNodeData Mesh::getDataFromMsh(const std::string& filename)
{
    gmsh::initialize();

    gmsh::open(filename);

    // get the mesh nodes
    std::vector<size_t> nodeTags;
    std::vector<double> nodeCoords, nodeParams;
    gmsh::model::mesh::getNodes(nodeTags, nodeCoords, nodeParams);

    std::vector<Eigen::Vector3d> coo;

    for (size_t i = 0; i< nodeCoords.size(); i+=3)
    {
        coo.emplace_back(nodeCoords[i], nodeCoords[i+1], nodeCoords[i+2]);
    }

    // get the mesh elements for the entity 
    std::vector<int> elemTypes; 
    std::vector<std::vector<std::size_t>> elemTags, elemNodeTags;
    gmsh::model::mesh::getElements(elemTypes, elemTags, elemNodeTags);

    std::vector<std::tuple<int, int, int, int>> elts;

    for (size_t i = 0; i < elemTypes.size(); ++i)
    {
        if(elemTypes[i] == 4)
        {
            const unsigned int nbNoeuds = elemNodeTags[i].size() / elemTags[i].size();
            for (size_t j = 0; j < elemNodeTags[i].size(); j+=nbNoeuds)
            {
                std::cout << elemNodeTags[i][j] - 1 << ", " << elemNodeTags[i][j+1] - 1 << ", " << elemNodeTags[i][j+2] - 1<< ", " << elemNodeTags[i][j+3] - 1 << "\n";
                elts.emplace_back(std::make_tuple(
                    elemNodeTags[i][j] - 1,
                    elemNodeTags[i][j + 1] - 1,
                    elemNodeTags[i][j + 2] - 1,
                    elemNodeTags[i][j + 3] - 1
                ));
            }
        }
    }

    gmsh::finalize();

    return std::make_pair(coo, elts);
}

void Mesh::exportVtkFile(const std::string& filename, const Mesh::EltsNodeData& data)
{
    const std::vector<Eigen::Vector3d>& nodes = std::get<0>(data);
    const std::vector<std::tuple<int, int, int, int>>& elts = std::get<1>(data);

    std::ofstream file(filename);

    file << "# vtk DataFile Version 2.0\n";
    file << "LINEAR TETRAHEDRON FEM\n";
    file << "ASCII\n\n";

    file << "DATASET UNSTRUCTURED_GRID\n\n";

    file << "POINTS " << nodes.size() << " double\n";
    for(const auto& node: nodes)
    {
        file << node(0) << " " << node(1) << " " << node(2) <<"\n";
    }

    file<<"\n";
    
    file << "CELLS " << elts.size() << " " << elts.size() * 4 << "\n";
    for(const auto& elt: elts)
    {
        file << "4 " << std::get<0>(elt) << " " 
                        << std::get<1>(elt) << " " 
                        << std::get<2>(elt) << " " 
                        << std::get<3>(elt) << "\n";
    }

    file<<"\n";

    file << "CELL_TYPES " << elts.size() << "\n";
    for(size_t i = 0; i < elts.size(); ++i)
    {
        file << "10\n";
    }
}

Mesh::~Mesh()
{
    gmsh::finalize();
}
}