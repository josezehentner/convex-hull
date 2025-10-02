#ifndef PRESETPOINTPROVIDER_H
#define PRESETPOINTPROVIDER_H

#include "IPointProvider.h"
#include <string>
#include <fstream>
#include <sstream>
#include <stdexcept>

class PresetPointProvider : public IPointProvider {

public:
    explicit PresetPointProvider(const std::string& filename);

    std::vector<Point> getPoints() override;

private:
    std::string m_filename;

};

#endif //PRESETPOINTPROVIDER_H
