#include <pause.h>

void Pause::setRenderer(Renderer* renderer) {
    _renderer = renderer;
}

void Pause::setPlay(bool showControls) {
    _options.clear();

    _options.push_back(Option("QUIT TO DESKTOP", GLOBAL::CLICK_OPTION));
    _options.push_back(Option("EXIT LEVEL", GLOBAL::CLICK_OPTION));
    _options.push_back(Option("SHOW CONTROLS", GLOBAL::BOOL_OPTION, showControls));
    _options.push_back(Option("RESUME", GLOBAL::CLICK_OPTION));

    _clicked = -1;
    _current = -1;
}

void Pause::setMenu(bool showControls) {
    _options.clear();

    _options.push_back(Option("QUIT TO DESKTOP", GLOBAL::CLICK_OPTION));
    _options.push_back(Option("SHOW CONTROLS", GLOBAL::BOOL_OPTION, showControls));
    _options.push_back(Option("RESUME", GLOBAL::CLICK_OPTION));

    _clicked = -1;
    _current = -1;
}

void Pause::mouseMove(glm::vec2 mousePos, float height) {
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
            _current = i;
            break;
        } else {
            _current = -1;
        }
        height += step;
    }
}

void Pause::click(bool click) {
    if (click) {
        _clicked = _current;
        if (_current != -1 && _options[_current].type == GLOBAL::BOOL_OPTION) {
            _options[_current].value = !_options[_current].value;
        }
    } else {
        _clicked = -1;
    }
}

void Pause::keyPress(int dir) {
    _current += dir;
    if (_current < 0) {
        _current = _options.size() - 1;
    } else if (_current > _options.size() - 1) {
        _current = 0;
    }
}

int Pause::clicked() {
    return _clicked;
}

void Pause::setCurrent(int x) {
    _current = x;
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

    for (int i = 0; i < _options.size(); i++) {
        Option option = _options[i];
        if (i == _current) {
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
