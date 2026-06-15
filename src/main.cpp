#include <memory>
#include <stdexcept>

#include "ConfigReader/ConfigReader.h"
#include "Objects/LogoObject.h"
#include "Objects/PauseTextObject.h"
#include "Window/Window.h"

int main() {
    const Config config = ConfigReader("config.json").ReadConfig();

    Window window(config, config.logoPaths);
    window.AddObject(std::make_unique<LogoObject>(config.logoPaths));
    window.AddObject(std::make_unique<PauseTextObject>(config.fontsPath));
    window.Run();

    return 0;
}
