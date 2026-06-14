#include <memory>
#include <stdexcept>

#include "ConfigReader/ConfigReader.h"
#include "Objects/LogoObject.h"
#include "Objects/PauseTextObject.h"
#include "Window/Window.h"

int main() {
    const Config config = ConfigReader("../../config.json").ReadConfig();

    std::vector<std::unique_ptr<RenderableObject>> objects;
    objects.push_back(std::make_unique<LogoObject>(config.logoPaths));
    objects.push_back(std::make_unique<PauseTextObject>(config.fontsPath));

    Window window(config, std::move(objects), config.logoPaths);
    window.Run();

    return 0;
}
