#include <pause.h>

void Pause::setRenderer(Renderer* renderer) {
    _renderer = renderer;
}

void Pause::setPlay() {
    _options.clear();

    _options.push_back(Option("QUIT TO DESKTOP", GLOBAL::CLICK_OPTION));
    _options.push_back(Option("EXIT LEVEL", GLOBAL::CLICK_OPTION));
    _options.push_back(Option("HIDE CONTROLS", GLOBAL::BOOL_OPTION));
    _options.push_back(Option("RESUME", GLOBAL::CLICK_OPTION));
}

void Pause::setMenu() {
    _options.clear();

    _options.push_back(Option("QUIT TO DESKTOP", GLOBAL::CLICK_OPTION));
    _options.push_back(Option("HIDE CONTROLS", GLOBAL::BOOL_OPTION));
    _options.push_back(Option("RESUME", GLOBAL::CLICK_OPTION));
}

void Pause::update(glm::vec2 mousePos) {

}

void Pause::resize(int w, int h) {
    _width = w;
    _height = h;
}

void Pause::draw(float height) {
    int step, textHeight, margin;
    float scale;
    if (_width < 500 || _height < 400) {
        step = 40;
        textHeight = 26;
        scale = -1;
        margin = GLOBAL::SMALL_BUTTON_MARGIN;
    } else {
        step = 60;
        textHeight = 39;
        scale = 1;
        margin = GLOBAL::LARGE_BUTTON_MARGIN;
    }

    height += (_height - _options.size()*step)/2.0f;

    for (Option option: _options) {
        if (option.type == GLOBAL::BOOL_OPTION) {
            _renderer->drawSquare(
                50 - margin,
                _width - 50 + margin,
                height - margin,
                height + textHeight + margin,
                GLOBAL::SELECTED_BUTTON_COLOR,
                GLOBAL::BUTTON_TRANSPARANCY
            );
        } else {
            _renderer->drawSquare(
                50 - margin,
                _width - 50 + margin,
                height - margin,
                height + textHeight + margin,
                GLOBAL::BUTTON_COLOR,
                GLOBAL::BUTTON_TRANSPARANCY
            );
        }
        if (option.type == GLOBAL::BOOL_OPTION) {
            _renderer->drawText(option.text, 50, height, scale, GLOBAL::TEXT_COLOR);
            _renderer->drawTextRight("YES", 50, height, scale, GLOBAL::TEXT_COLOR);
        } else if (option.type == GLOBAL::CLICK_OPTION) {
            _renderer->drawText(option.text, 50, height, scale, GLOBAL::TEXT_COLOR);
        }
        height += step;
    }
}
