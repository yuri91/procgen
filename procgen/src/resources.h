#pragma once

/*

Load assets stored as individual image files

*/

#include <QtGui/QPainter>
#include <iostream>
#include <memory>
#include <cheerp/client.h>

std::shared_ptr<QImage> get_asset_ptr(std::string relpath);

extern std::string global_resource_root;
extern client::Promise* images_load();
extern std::vector<std::shared_ptr<QImage>> topdown_backgrounds;
extern std::vector<std::shared_ptr<QImage>> topdown_simple_backgrounds;
extern std::vector<std::shared_ptr<QImage>> platform_backgrounds;
extern std::vector<std::shared_ptr<QImage>> space_backgrounds;
extern std::vector<std::shared_ptr<QImage>> water_backgrounds;
extern std::vector<std::shared_ptr<QImage>> water_surface_backgrounds;
