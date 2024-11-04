#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

bool state = true;
std::vector<int> a;

class line {
private:
public:
  void draw(sf::RenderWindow &win);
  void reshuffle(unsigned int NumberOfpoints);
  void bubblesort(sf::RenderWindow &win);
  void insertionsort(sf::RenderWindow &win);
  void display(sf::RenderWindow &win, unsigned int index);
};
void game() {
  sf::RenderWindow Window(sf::VideoMode(1000, 800), "Algorithm Visualizer", sf::Style::Titlebar | sf::Style::Close );
  sf::Clock r;
  line Line = line();
  Line.reshuffle(100);
  while (Window.isOpen()) {
    sf::Event event;
    while (Window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        Window.close();
      }
      if (event.type == sf::Event::KeyPressed) {
        state = true;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
          std::random_shuffle(std::begin(a), std::end(a));
          Line.display(Window, -1);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
          Line.insertionsort(Window);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::B)) {
          Line.bubblesort(Window);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
          Window.close();
        }
      }
      Window.display();
    }
  }
}

int main() { game(); }

void line::reshuffle(unsigned int NumberOfPoints) {
  for (int i = 1; i < NumberOfPoints; i++) {
    a.push_back(i);
  }
  std::random_shuffle(a.begin(), a.end());
}
void line::bubblesort(sf::RenderWindow &win) {
  while (!std::is_sorted(a.begin(), a.end())) {
    for (unsigned i = 0; i < a.size(); i++) {
      if (a[i] > a[i + 1]) {
        std::iter_swap(a.begin() + i, a.begin() + i + 1);
      }
      line::display(win, i);
    }
  }
}
void line::insertionsort(sf::RenderWindow &win) {
  for (unsigned int i = 1; i < a.size(); i++) {
    int k = a[i];
    int j = i - 1;
    while (j >= 0 && a[j] > k) {
      a[j + 1] = a[j];
      j--;
      line::display(win, j);
    }
    a[j + 1] = k;
    line::display(win, i + 1);
  }
}
void line::display(sf::RenderWindow &win, unsigned int index) {
  sf::RectangleShape shape(sf::Vector2f(10, 1));
  shape.setRotation(180.0f);
  win.clear(sf::Color::Black);
  for (unsigned int i = 1; i < a.size(); i++) {
    shape.setSize(sf::Vector2f(8, a[i] * 4));
    shape.setPosition(i * 10, 800);
    if (i - 1 == index)
      shape.setFillColor(sf::Color::Red);
    else
      shape.setFillColor(sf::Color::White);
    win.draw(shape);
  }
  win.display();
}
