#include <pause.h>

void Pause::setRenderer(Renderer* renderer) {
    _renderer = renderer;
}

void Pause::setPlay() {
    _options.clear();

    _options.push_back(Option("QUIT TO DESKTOP", GLOBAL::CLICK_OPTION));
    _options.push_back(Option("EXIT LEVEL", GLOBAL::CLICK_OPTION));
    _options.push_back(Option("SHOW CONTROLS", GLOBAL::BOOL_OPTION));
    _options.push_back(Option("RESUME", GLOBAL::CLICK_OPTION));

    _clicked = -1;
}

void Pause::setMenu() {
    _options.clear();

    _options.push_back(Option("QUIT TO DESKTOP", GLOBAL::CLICK_OPTION));
    _options.push_back(Option("SHOW CONTROLS", GLOBAL::BOOL_OPTION));
    _options.push_back(Option("RESUME", GLOBAL::CLICK_OPTION));

    _clicked = -1;
}

void Pause::update(glm::vec2 mousePos, float height) {
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

    height += (_height - ((_options.size() - 1)*step + textHeight + margin))/2.0f;

    for (int i = 0; i < _options.size(); i++) {
        if (
            50 - margin < mousePos.x
            && _width - 50 + margin > mousePos.x
            && height - margin < mousePos.y
            && height + textHeight + margin > mousePos.y
        ) {
            _options[i].hover = true;
        } else {
            _options[i].hover = false;
        }
        height += step;
    }
}

void Pause::click(bool mouseClick) {
    if (mouseClick) {
        for (int i = 0; i < _options.size(); i++) {
            if (_options[i].hover) {
                _clicked = i;
                if (_options[i].type == GLOBAL::BOOL_OPTION) {
                    _options[i].value = !_options[i].value;
                }
            }
        }
    } else {
        _clicked = -1;
    }
}

int Pause::clicked() {
    return _clicked;
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

    height += (_height - ((_options.size() - 1)*step + textHeight + margin))/2.0f;

    for (Option option: _options) {
        if (option.hover) {
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
            if (option.value) {
                _renderer->drawTextRight("YES", 50, height, scale, GLOBAL::TEXT_COLOR);
            } else {
                _renderer->drawTextRight("NO", 50, height, scale, GLOBAL::TEXT_COLOR);
            }
        } else if (option.type == GLOBAL::CLICK_OPTION) {
            _renderer->drawText(option.text, 50, height, scale, GLOBAL::TEXT_COLOR);
        }
        height += step;
    }
}
