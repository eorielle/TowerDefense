#include"Field.h"

//Constructors and destroyers
Field::Field()
{
	width = TILE_WIDTH * TILE_NUM_HOR;
	height = TILE_HEIGHT * TILE_NUM_VER;
	numTileHor = TILE_NUM_HOR;
	numTileVer = TILE_NUM_VER;
	for (int i = 0; i < TILE_NUM_HOR*TILE_NUM_VER; i++)
	{
		tilesMap.emplace_back(i / TILE_NUM_HOR, i % TILE_NUM_HOR);//construct the map of tiles
	}
	startTile = tilesMap[NUM_START_TILE];
	endTile = tilesMap[NUM_END_TILE];
	boundingBox = sprite.getGlobalBounds();
}

Field::~Field(){}

//Getters
int Field::getWidth()
{
	return width;
}

int Field::getHeight()
{
	return height;
}

int Field::getNumTileHor()
{
	return numTileHor;
}

int Field::getNumTileVer()
{
	return numTileVer;
}

Tile* Field::getTile(int n)
{
	Tile *t;
	*t = tilesMap[n];
	return t;
}

Tile* Field::getTile(sf::Vector2i _position)
{
	Tile *t;
	*t = tilesMap[_position.x*TILE_NUM_HOR+_position.y];
	return t;
}

Tile* Field::getStartTile()
{
	Tile* pTile;
	pTile = LevelManager::getLevelManager().getField().getTile(NUM_START_TILE);
	return pTile;
}

Tile* Field::getEndTile()
{
	Tile* pTile;
	pTile = LevelManager::getLevelManager().getField().getTile(NUM_END_TILE);
	return pTile;
}

sf::Sprite Field::getSprite()
{
	return sprite;
}

//Setters

void Field::setSprite(sf::Sprite mySprite)
{
	sprite = mySprite;
}

//Functions

bool Field::mouseHover()
{
	bool isHovering = false;
	sf::Vector2f mousePosition((float)sf::Mouse::getPosition().x, (float)sf::Mouse::getPosition().y);

	if (boundingBox.contains(mousePosition))
	{
		isHovering = true;
		//updatesprite
	}
	else
	{
		isHovering = false;
		//updatesprite
	}

	return isHovering;
}

bool Field::mouseClicking(sf::Event event)
{
	if (mouseHover())
	{
		if (event.type == sf::Event::MouseButtonPressed)
		{
			return true;
			//updatesprite
		}
	}
	return false;
}

bool Field::mouseClick(sf::Event event)
{
	if (mouseClicking(event))
	{
		if (event.type == sf::Event::MouseButtonReleased)
		{
			return true;
			//updatesprite
		}
	}
	return false;
}
void Field::draw(sf::RenderWindow& w)
{
	w.draw(sprite);
}

int Field::timeCross(int m, int n)  //Dijkstra
{


	int t[TILE_NUM_HOR*TILE_NUM_VER][TILE_NUM_HOR*TILE_NUM_VER]; //build matrice of graph TILE_NUM_HOR*TILE_NUM_VER, TILE_NUM_HOR*TILE_NUM_VER Tiles

	for (int i = 0; i < TILE_NUM_HOR*TILE_NUM_VER; i++)
	{
		for (int j = 0; j < TILE_NUM_HOR*TILE_NUM_VER; j++)
		{
			if (i == j + 1 || i == j - 1 || i == j + TILE_NUM_VER || i == j - TILE_NUM_VER)
				t[i][j] = 1; // exist arret{ Tile i, Tile j}
			if (i == j)
				t[i][j] = 0;

			t[i][j] = 999;       // no arret { Tile i, Tile j}
		};                           
	};
	for (int k = 0; k < TILE_NUM_HOR*TILE_NUM_VER; k++)
	{
		Tile tile(k / TILE_NUM_VER, k % TILE_NUM_VER);
		if (tile.hasTower() == 1)
		{
			for (int l = 0; l < TILE_NUM_HOR*TILE_NUM_VER; l++)
			{
				t[k][l] = 999;
				t[l][k] = 999;
			}
		}
	}                  // no path if has tower


	int V[TILE_NUM_HOR * TILE_NUM_VER];  //is in the group
	int D[TILE_NUM_HOR * TILE_NUM_VER];  //distanceV[m] = 1;
	
	for (int c = 0; c <= TILE_NUM_HOR*TILE_NUM_VER; c++)
	{
		D[c] = t[m][c];
	}

	for (int f = 0; f < TILE_NUM_HOR*TILE_NUM_VER; f++)
	{
		int sum;
		int temp = 999, w = m;
		for (int d = 0; d < TILE_NUM_HOR*TILE_NUM_VER; d++)
		{
			if (V[d] == 0 && D[d] < temp)
			{
				temp = D[d];
				w = d;
			}
		}
		V[w] = 1;
		for (int k = 0; k < TILE_NUM_HOR*TILE_NUM_VER; k++)
		{
			if (V[k] == 0)
			{
				sum = D[w] + t[w][k];
				if (sum < D[k])
				{
					D[k] = sum;
				}
			}
		}
	}
	return D[n];

}

Path Field::computePath(Tile _startTile, Tile _endTile)
{
	sf::Vector2i vec1 = _startTile.getPosition();
	sf::Vector2i vec2 = _endTile.getPosition();
	int m = vec1.x / TILE_WIDTH + vec1.y * TILE_NUM_VER / TILE_HEIGHT;  //  point de depart
	int n = vec2.x / TILE_WIDTH + vec2.y * TILE_NUM_VER / TILE_HEIGHT; // point d'arrive
	int time = timeCross(m, n);
	vector<Tile> path;
	path[0] = _startTile;
	int g = m;
	for (int r = 1; r < time; r++)
	{
		if (time == timeCross(g + TILE_NUM_VER, n) + timeCross(m, g + TILE_NUM_VER))
			g += TILE_NUM_VER;
		if (time == timeCross(g + 1, n) + timeCross(m, g + 1))
			g += 1;
		if (time == timeCross(g - 1, n) + timeCross(m, g - 1))
			g -= 1;
		Tile tile(g / TILE_NUM_VER, g % TILE_NUM_VER);
		path[r] = tile;
	}
	return path;
}

bool Field::tryCross(Tile _startTile, Tile _endTile)
{
	sf::Vector2i vec1 = _startTile.getPosition();
	sf::Vector2i vec2 = _endTile.getPosition();
	int m = vec1.x / TILE_WIDTH + vec1.y * TILE_NUM_VER / TILE_HEIGHT;  //  point de depart
	int n = vec2.x / TILE_WIDTH + vec2.y * TILE_NUM_VER / TILE_HEIGHT; // point d'arrive

	//trycross from depart tile
	int time = timeCross(m, n);
	if (time > TILE_NUM_HOR*TILE_NUM_VER)
		return false;

	//try cross for all the enemies on the field
	LevelManager levelManager = LevelManager::getLevelManager();
	vector<Enemy*> enemies;
	enemies = levelManager.getEnemies();//get the list of enemies
	for (int i = 0; i < enemies.size(); i++)
	{
		Enemy *enemy = enemies[i];
		Tile tile = (*enemy).getTile();
		sf::Vector2i vec3 = tile.getPosition();
		int p = vec3.x / TILE_WIDTH + vec3.y * TILE_NUM_VER / TILE_HEIGHT;  //  point d'enemy
		time = timeCross(p, n);
		if (time > TILE_NUM_HOR*TILE_NUM_VER)
			return false;  //enemy i can't cross
	}
	//all the enemis on the field and enemies that will appear on the field can cross
	return true;
}