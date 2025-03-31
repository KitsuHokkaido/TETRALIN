#include <Eigen/Dense>

#include <array>
#include <vector>

namespace lin_tetra
{
class FEM
{
public:
    FEM() = delete;
    FEM(double v, double E);
    ~FEM();

public:
    Eigen::VectorXd Run(const std::vector<Eigen::Vector3d>& coo, 
        const std::vector<std::tuple<int, int, int, int>>& elts);

private:
    Eigen::Matrix<double, 12, 12> calcul_Ke(const std::array<Eigen::Vector3d, 4>& coo);
    Eigen::MatrixXd assemblage_K(const std::vector<Eigen::Vector3d>& coo, const std::vector<std::tuple<int, int, int, int>>& elts);

private:
    Eigen::Matrix<double, 9, 12> X; 
    Eigen::Matrix<double, 6, 6> D;
    Eigen::Matrix<double, 6, 9> A;
    const double E, v;
};
}