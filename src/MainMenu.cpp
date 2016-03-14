#include <include/MainMenu.hpp>

MainMenu::MainMenu(tinyxml2::XMLElement* root) {
	_ASSERT(root->Name() == std::string("MainMenu"));

	mBackground.setTexture(
		ResourceManager<sf::Texture>::instance()->get(
			root->FirstChildElement("Backdrop")->Attribute("path")
		)//end get()
	);//end setTexture()

	mMusic.openFromFile(
		root->FirstChildElement("Music")->Attribute("path")
	);//end openFromFile()

	mMusic.setLoop(true);
	
	auto startBtnXml = root->FirstChildElement("StartButton");
	mStartButton = std::make_unique<gui::Button>(
		atoi(startBtnXml->Attribute("x")),
		atoi(startBtnXml->Attribute("y")),
		startBtnXml
	);

	auto quitBtnXml = root->FirstChildElement("QuitButton");
	mQuitButton = std::make_unique<gui::Button>(
		atoi(quitBtnXml->Attribute("x")),
		atoi(quitBtnXml->Attribute("y")),
		quitBtnXml
	);
}

MainMenu::~MainMenu() {}

bool MainMenu::handleEvent(sf::Event& evnt) {
	bool handled = false;

	switch (evnt.type) {
		default:
			break;
		case sf::Event::MouseButtonPressed:
			handled = true;
			if (mStartButton->checkClick()) {
				//start the game
				SceneManager::instance()->navigateToScene("LevelOne");
			} else if (mQuitButton->checkClick()) {
				//quit the game
				Game::close();
			}
			break;
		case sf::Event::MouseButtonReleased:
			break;
		case sf::Event::MouseMoved:
			auto mousePos = sf::Vector2i(evnt.mouseMove.x, evnt.mouseMove.y);
			mStartButton->update(mousePos);
			mQuitButton->update(mousePos);
			handled = true;
			break;
	}

	return handled;
}

void MainMenu::update(sf::Time const& elapsedTime) {
	if (mMusic.getStatus() != sf::Music::Status::Playing) {
		mMusic.play();
	}
}

void MainMenu::draw(sf::RenderWindow &w) {
	w.draw(mBackground);
	mStartButton->draw(w);
	mQuitButton->draw(w);
}

void MainMenu::cleanup() {
	mMusic.stop();
}
