#include "FEM.hpp"
#include "Mesh.hpp"

using namespace lin_tetra;

int main()
{
    auto [nodes, elts] = Mesh::getDataFromMsh("cylinder.msh");

    //Mesh::exportVtkFile("cylinder.vtk", std::make_pair(nodes, elts));

    FEM fem(0.3, 2.5e11);

    Mesh::exportUFile("deplacement.txt", fem.Run(nodes, elts));
}