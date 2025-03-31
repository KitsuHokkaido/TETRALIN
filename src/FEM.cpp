#include "FEM.hpp"

#include <iostream>

namespace lin_tetra
{
FEM::FEM(double v, double E):
    v(v), E(E)
{
    D <<    1-v, v, v, 0, 0, 0,
            v, 1-v, v, 0, 0, 0,
            v, v, 1-v, 0, 0, 0,
            0, 0, 0, (1-2*v)/2, 0, 0,
            0, 0, 0, 0, (1-2*v)/2, 0,
            0, 0, 0, 0, 0, (1-2*v)/2;

    D = (E/((1 + v)*(1-2*v)))*D;

    X <<    -1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0,
            0, -1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,
            0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
            0, -1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0,
            -1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,
            -1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 
            0, 0, -1, 0, 0, 1, 0, 0, 0, 0, 0, 0,
            0, 0, -1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 
            0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0;

    A <<    1, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 1, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 1, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0.5, 0.5, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0.5, 0.5, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0.5, 0.5;
}

FEM::~FEM()
{

}

void FEM::Run(const std::vector<Eigen::Vector3d>& coo, 
    const std::vector<std::tuple<int, int, int, int>>& elts)
{
    Eigen::MatrixXd K = assemblage_K(coo, elts);

}

Eigen::Matrix<double, 12, 12> FEM::calcul_Ke(const std::array<Eigen::Vector3d, 4>& coo)
{
    Eigen::Matrix<double, 3, 3> J;

    const Eigen::Vector3d& N1 = coo[0];
    const Eigen::Vector3d& N2 = coo[1];
    const Eigen::Vector3d& N3 = coo[2];
    const Eigen::Vector3d& N4 = coo[3];

    J <<    N2(0) - N1(0), N2(1) - N1(1), N2(2) - N1(2),
            N3(0) - N1(0), N3(1) - N1(1), N3(2) - N1(2),
            N4(0) - N1(0), N4(1) - N1(1), N4(2) - N1(2);


    Eigen::MatrixXd J_inv = J.inverse();

    Eigen::Matrix<double, 9, 9> J_tot = Eigen::Matrix<double, 9, 9>::Zero();

    J_tot.block<3, 3>(0, 0) = J_inv;
    J_tot.block<3, 3>(3, 3) = J_inv;
    J_tot.block<3, 3>(6, 6) = J_inv;

    Eigen::MatrixXd B = A * J_tot * X;
    
    std::cout << std::abs(J.determinant()) << std::endl;

    return (0.16666666666)*(std::abs(J.determinant()) * B.transpose() * D * B);
}

Eigen::MatrixXd FEM::assemblage_K(const std::vector<Eigen::Vector3d>& coo, 
    const std::vector<std::tuple<int, int, int, int>>& elts)
{
    Eigen::MatrixXd K = Eigen::MatrixXd::Zero(coo.size() * 3, coo.size() * 3);
    for(const auto& elt: elts)
    {
        const std::array<Eigen::Vector3d, 4>& coo_elt = {
            coo[std::get<0>(elt)],
            coo[std::get<1>(elt)],
            coo[std::get<2>(elt)],
            coo[std::get<3>(elt)]
        };

        Eigen::Matrix<double, 12, 12> Ke = calcul_Ke(coo_elt);

        const std::array<size_t, 12> guide_elts_noeuds = {
            3 * std::get<0>(elt), 3 * std::get<0>(elt) + 1, 3 * std::get<0>(elt) + 2,
            3 * std::get<1>(elt), 3 * std::get<1>(elt) + 1, 3 * std::get<1>(elt) + 2,
            3 * std::get<2>(elt), 3 * std::get<2>(elt) + 1, 3 * std::get<2>(elt) + 2,
            3 * std::get<3>(elt), 3 * std::get<3>(elt) + 1, 3 * std::get<3>(elt) + 2,  
        };

        for(size_t i = 0; i < 12; ++i)
        {
            for(size_t j = 0; j < 12; ++j)
            {
                K(guide_elts_noeuds[i], guide_elts_noeuds[j]) += Ke(i, j);
            }
        }

    }

    return K;
}
}