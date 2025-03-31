#include <string>
#include <vector>
#include <tuple>

#include <Eigen/Dense>

namespace lin_tetra
{
class Mesh
{
    using EltsNodeData = std::pair<std::vector<Eigen::Vector3d>, std::vector<std::tuple<int, int, int, int>>>;
public:
    Mesh();
    ~Mesh();

public:
    static EltsNodeData getDataFromMsh(const std::string& filename);
    static void exportVtkFile(const std::string& filename, const EltsNodeData& data);
};
}