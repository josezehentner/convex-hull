#ifndef PRESETPOINTPROVIDER_H
#define PRESETPOINTPROVIDER_H

#include "IPointProvider.h"
#include <string>
#include <fstream>
#include <sstream>
#include <stdexcept>

class FromFilePointProvider : public IPointProvider {

public:
    explicit FromFilePointProvider(const std::string& filename);

    std::vector<Point> getPoints() override;

private:
    std::string m_filename;

};

#endif //PRESETPOINTPROVIDER_H
