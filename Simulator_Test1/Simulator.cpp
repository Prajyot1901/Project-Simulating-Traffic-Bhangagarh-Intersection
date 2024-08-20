#include<iostream>
#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<queue>
#include<map>
#include<fstream>
#include<sstream>
using namespace sf;
using namespace std;
class vehicle
{
public:
	RectangleShape v;
	float speed;
	int turn;
	float maxspeed;
	vehicle(RectangleShape car,int m,int t)
	{
		this->v = car;
		this->speed = m;
		this->turn = t;
		if (car.getSize().x > 25 || car.getSize().y > 25)
		{
			this->maxspeed = 4;
			this->speed = 4;
		}
		else
			this->maxspeed = 5;
	}
};
class approach
{
public:
	queue<vehicle*> lane1;
	queue<vehicle*> lane2;
	queue<vehicle*> lane3;

	void add( int v, Vector2f pos, int t,int config,int l,string type)
	{
		if (type =="car" || type=="bike")
		{
			if (config == 0)
			{
				RectangleShape s(Vector2f(15, 10));
				s.setPosition(pos);
				if (type == "bike")
				{
					s.setFillColor(Color::Blue);
				}
				vehicle* car = new vehicle(s, v, t);
				if (l == 1)
				{
					lane1.push(car);
				}
				else if (l == 2)
				{
					lane2.push(car);
				}
				else
				{
					lane3.push(car);
				}
			}
			else
			{
				RectangleShape s(Vector2f(10.f, 15.f));
				s.setPosition(pos);
				if (type == "bike")
				{
					s.setFillColor(Color::Blue);
				}
				vehicle* car = new vehicle(s, v, t);
				if (l == 1)
					lane1.push(car);
				else if (l == 2)
				{
					lane2.push(car);
				}
				else
				{
					lane3.push(car);
				}
			}
		}
		else if (type == "hcv")
		{
			if (config == 0)
			{
				RectangleShape s(Vector2f(30, 12));
				s.setPosition(pos);
				s.setFillColor(Color::Red);
				vehicle* car = new vehicle(s, v, t);
				if (l == 1)
				{
					lane1.push(car);
				}
				else if (l == 2)
				{
					lane2.push(car);
				}
				else
				{
					lane3.push(car);
				}
			}
			else
			{
				RectangleShape s(Vector2f(10.f, 30.f));
				s.setPosition(pos);
				s.setFillColor(Color::Red);
				vehicle* car = new vehicle(s, v, t);
				if (l == 1)
					lane1.push(car);
				else if (l == 2)
				{
					lane2.push(car);
				}
				else
				{
					lane3.push(car);
				}
			}
		}
	}
};
class intersection
{
public:
	int s_east = 0;
	int s_west = 0;
	int s_north = 1;
	approach east;
	approach east_1;
	approach west;
	approach west_1;
	approach north;
	approach north_1;
	intersection()
	{
		east =	approach();
		west = approach();
		north = approach();
		east_1= approach();
		west_1= approach();
		north_1 = approach();
	}
};

//Update

void Update(intersection &Bhan,float &wait,float &N_wait,float &E_wait,float &W_wait)
{
	approach temp = Bhan.east;
	queue<vehicle*> lane1 = temp.lane1;
	queue<vehicle*> lane2 = temp.lane2;
	queue<vehicle*> lane3 = temp.lane3;
	float pre;




	if (Bhan.s_east == 0)
	{
		pre = 898;
	}
	else
		pre = 898;
	while (!lane1.empty())
	{
		if (lane1.front()->speed <= 1)
		{
			E_wait++;
		}
		if (lane1.front()->v.getPosition().x >= 860)
		{
			//cout << E_wait << endl;
			lane1.front()->v.rotate(-90.f);
			Bhan.north_1.lane1.push(lane1.front());
			Bhan.east.lane1.pop();
		}

		lane1.front()->v.move(Vector2f(lane1.front()->speed, 0));
		if ((pre - 5) - (lane1.front()->v.getPosition().x + lane1.front()->v.getSize().x) < lane1.front()->speed*15)
		{
			lane1.front()->speed = max(0.f, ((pre - 5) - (lane1.front()->v.getPosition().x + lane1.front()->v.getSize().x)) / 15);
		}
		else if (lane1.front()->speed < lane1.front()->maxspeed)
		{
			lane1.front()->speed += 1.0 / 15;
		}
		pre = lane1.front()->v.getPosition().x;
		lane1.pop();
	}

	if (Bhan.s_east == 0)
	{
		pre = 853;
	}
	else
		pre = 1800;
	while (!lane2.empty())
	{
		if (lane2.front()->speed <= 1)
		{
			E_wait++;
		}
		if (lane2.front()->v.getPosition().x >= 878)
		{
			//cout << E_wait << endl;
			if (lane2.front()->turn == 0)
			{
				Bhan.west_1.lane2.push(lane2.front());
			}
			else if (lane2.front()->turn == -1)
			{
				lane2.front()->v.rotate(-90.f);
				Bhan.north_1.lane2.push(lane2.front());
			}
			Bhan.east.lane2.pop();
		}


		lane2.front()->v.move(Vector2f(lane2.front()->speed, 0));
		if ((pre - 5) - (lane2.front()->v.getPosition().x + lane2.front()->v.getSize().x) < lane2.front()->speed * 15)
		{
			lane2.front()->speed = max(0.f,((pre - 5) - (lane2.front()->v.getPosition().x + lane2.front()->v.getSize().x)) / 15);
		}
		else if (lane2.front()->speed < lane2.front()->maxspeed)
		{
			lane2.front()->speed += 1.0 / 15;
		}
		pre = lane2.front()->v.getPosition().x;
		lane2.pop();
	}

	if (Bhan.s_east == 0)
	{
		pre = 853;
	}
	else
		pre = 1800;
	while (!lane3.empty())
	{
		if (lane3.front()->speed <= 1)
		{
			E_wait++;
		}
		if (lane3.front()->v.getPosition().x >= 878)
		{
			if (lane3.front()->turn == 0)
			{
				Bhan.west_1.lane3.push(lane3.front());
			}
			Bhan.east.lane3.pop();
		}



		lane3.front()->v.move(Vector2f(lane3.front()->speed, 0));
		if ((pre - 5) - (lane3.front()->v.getPosition().x + lane3.front()->v.getSize().x) < lane3.front()->speed * 15)
		{
			lane3.front()->speed = max(0.f,((pre - 5) - (lane3.front()->v.getPosition().x + lane3.front()->v.getSize().x)) / 15);
		}
		else if (lane3.front()->speed < lane3.front()->maxspeed)
		{
			lane3.front()->speed += 1.0 / 15;
		}
		pre = lane3.front()->v.getPosition().x;
		lane3.pop();
	}




	temp = Bhan.north;
	lane1 = temp.lane1;
	lane2 = temp.lane2;
	lane3 = temp.lane3;

	if (Bhan.s_north == 0)
	{
		pre = 645;
	}
	else
	{
		pre = 780;
	}
	while (!lane1.empty())
	{
		if (lane1.front()->speed <= 1)
		{
			N_wait ++;
		}
		if (lane1.front()->turn == 1)
		{
			if (lane1.front()->v.getPosition().y >= 720)
			{
				lane1.front()->v.rotate(90.f);
				Bhan.east_1.lane1.push(lane1.front());
				Bhan.north.lane1.pop();
			}

			lane1.front()->v.move(Vector2f(0 , lane1.front()->speed));
			if ((pre - 5) - (lane1.front()->v.getPosition().y + lane1.front()->v.getSize().y) < lane1.front()->speed * 15)
			{
				lane1.front()->speed = max(0.f,((pre - 5) - (lane1.front()->v.getPosition().y + lane1.front()->v.getSize().y)) / 15);
			}
			else if (lane1.front()->speed < lane1.front()->maxspeed)
			{
				lane1.front()->speed += 1.0 / 15;
			}
			pre = lane1.front()->v.getPosition().y;
			lane1.pop();
		}
	}


	if (Bhan.s_north == 0)
	{
		pre = 695;
	}
	else
	{
		pre = 695;
	}
	while (!lane2.empty())
	{
		if (lane2.front()->speed <= 1)
		{
			N_wait++;
		}
		if (lane2.front()->v.getPosition().y >= 652)
		{
			//cout << N_wait/60 << endl;
			lane2.front()->v.rotate(90.f);
			Bhan.west_1.lane1.push(lane2.front());
			Bhan.north.lane2.pop();
		}



		lane2.front()->v.move(Vector2f(0, lane2.front()->speed));
		if ((pre - 5) - (lane2.front()->v.getPosition().y + lane2.front()->v.getSize().y) < lane2.front()->speed * 15)
		{
			lane2.front()->speed = max(0.f,((pre - 5) - (lane2.front()->v.getPosition().y + lane2.front()->v.getSize().y)) / 15);
		}
		else if (lane2.front()->speed < lane2.front()->maxspeed)
		{
			lane2.front()->speed += 1.0 / 15;
		}
		pre = lane2.front()->v.getPosition().y;
		lane2.pop();
	}


	temp = Bhan.west;
	lane1 = temp.lane1;
	lane2 = temp.lane2;
	lane3 = temp.lane3;

	if (Bhan.s_west == 0)
		pre = 950;
	else
		pre = 864;
	while (!lane1.empty())
	{
		int flag = 0;
		if (lane1.front()->speed <= 1)
		{
			W_wait++;
		}
		if (lane1.front()->v.getPosition().x <= 884)
		{
			lane1.front()->v.rotate(-90.f);
			Bhan.north_1.lane2.push(lane1.front());
			Bhan.west.lane1.pop();
		}

		lane1.front()->v.move(Vector2f((-1)* (lane1.front()->speed), 0.f));
		if ((lane1.front()->v.getPosition().x) - (pre + 5) < lane1.front()->speed * 15)
		{
			lane1.front()->speed = max(0.f,((lane1.front()->v.getPosition().x) - (pre + 5)) / 15);
			if (lane1.front()->v.getPosition().x < 945 && lane1.front()->speed == 0)
			{
				flag = 1;
				lane1.front()->speed = 1;
			}
		}
		else if (lane1.front()->speed < lane1.front()->maxspeed)
		{
			lane1.front()->speed = lane1.front()->speed + 1.0 / 15;
		}
		pre = lane1.front()->v.getPosition().x + lane1.front()->v.getSize().x;
		if (flag == 1)
		{
			pre = 950;
		}
		lane1.pop();
	}

	if (Bhan.s_west == 0)
		pre = 950;
	else
		pre = 0;
	while (!lane2.empty())
	{
		if (lane2.front()->speed <= 1)
		{
			W_wait ++;
		}
		if (lane2.front()->v.getPosition().x <= 868)
		{
			if (lane2.front()->turn == 1)
			{
				lane2.front()->v.rotate(-90.f);
				Bhan.north_1.lane1.push(lane2.front());
			}
			else
			{
				Bhan.east_1.lane2.push(lane2.front());
			}
			Bhan.west.lane2.pop();
		}

		lane2.front()->v.move(Vector2f((-1) * (lane2.front()->speed), 0.f));
		if ((lane2.front()->v.getPosition().x) - (pre + 5) < lane2.front()->speed * 15)
		{
			lane2.front()->speed = max(0.f,((lane2.front()->v.getPosition().x) - (pre + 5)) / 15);
			if (lane2.front()->v.getPosition().x < 945 && lane2.front()->speed == 0)
			{
				lane2.front()->speed = 1 ;
			}

		}
		else if (lane2.front()->speed < lane2.front()->maxspeed)
		{
			lane2.front()->speed = lane2.front()->speed + 1.0 / 15;
		}
		pre = lane2.front()->v.getPosition().x + lane2.front()->v.getSize().x;
		lane2.pop();
	}

	if (Bhan.s_west == 0)
		pre = 950;
	else
		pre = 0;
	while (!lane3.empty())
	{
		if (lane3.front()->speed <= 1)
		{
			W_wait ++;
		}
		if (lane3.front()->v.getPosition().x <= 864)
		{
			Bhan.east_1.lane3.push(lane3.front());
			Bhan.west.lane3.pop();
		}

		lane3.front()->v.move(Vector2f((-1)* (lane3.front()->speed), 0.f));
		if ((lane3.front()->v.getPosition().x) - (pre + 5) < lane3.front()->speed * 15)
		{
			lane3.front()->speed = max(0.f,((lane3.front()->v.getPosition().x) - (pre + 5)) / 15);
		}
		else if (lane3.front()->speed < lane3.front()->maxspeed)
		{
			lane3.front()->speed = lane3.front()->speed + 1.0 / 15;
		}
		pre = lane3.front()->v.getPosition().x + lane3.front()->v.getSize().x;
		lane3.pop();
	}

	

	temp = Bhan.east_1;
	lane1 = temp.lane1;
	lane2 = temp.lane2;
	lane3 = temp.lane3;

	pre = -50;
	while (!lane1.empty())
	{
		if (lane1.front()->speed <= 1/10)
		{
			wait =wait + 1.0 / 60;
		}
		if (lane1.front()->v.getPosition().x <= 0)
		{
			Bhan.east_1.lane1.pop();
		}

		lane1.front()->v.move(Vector2f((-1)*(lane1.front()->speed), 0));
		if ((lane1.front()->v.getPosition().x)-(pre + 5) < lane1.front()->speed)
		{
			lane1.front()->speed = max(0.f,((lane1.front()->v.getPosition().x) - (pre + 5)) / 15);
		}
		else
		{
			if (lane1.front()->speed < lane1.front()->maxspeed)
			{
				lane1.front()->speed = lane1.front()->speed + 1.0 / 15;
			}
		}
		pre = lane1.front()->v.getPosition().x + lane1.front()->v.getSize().x;
		lane1.pop();
	}
	pre = -50;
	while (!lane2.empty())
	{
		if (lane2.front()->speed <= 1/10)
		{
			wait = wait + 1.0 / 60;
		}
		if (lane2.front()->v.getPosition().x <= 0)
		{
			Bhan.east_1.lane2.pop();
		}

		lane2.front()->v.move(Vector2f((-1) * (lane2.front()->speed), 0));
		if ((lane2.front()->v.getPosition().x) - (pre + 5) < lane2.front()->speed)
		{
			lane2.front()->speed = max(0.f,((lane2.front()->v.getPosition().x) - (pre + 5)) / 15);
		}
		else
		{
			if (lane2.front()->speed < lane2.front()->maxspeed)
			{
				lane2.front()->speed = lane2.front()->speed + 1.0 / 15;
			}
		}
		pre = lane2.front()->v.getPosition().x + lane2.front()->v.getSize().x;
		lane2.pop();
	}
	pre = -50;
	while (!lane3.empty())
	{
		if (lane3.front()->speed <= 1/10)
		{
			wait = wait + 1.0 / 60;
		}
		if (lane3.front()->v.getPosition().x <= 0)
		{
			Bhan.east_1.lane3.pop();
		}

		lane3.front()->v.move(Vector2f((-1) * (lane3.front()->speed), 0));
		if ((lane3.front()->v.getPosition().x) - (pre + 5) < lane3.front()->speed)
		{
			lane3.front()->speed = max(0.f,((lane3.front()->v.getPosition().x) - (pre + 5)) / 15);
		}
		else
		{
			if (lane3.front()->speed < lane3.front()->maxspeed)
			{
				lane3.front()->speed = lane3.front()->speed + 1.0 / 15;
			}
		}
		pre = lane3.front()->v.getPosition().x + lane3.front()->v.getSize().x;
		lane3.pop();
	}

	temp = Bhan.west_1;
	lane1 = temp.lane1;
	lane2 = temp.lane2;
	lane3 = temp.lane3;

	pre = 1900;
	while (!lane1.empty())
	{
		if (lane1.front()->speed <= 1/10)
		{
			wait = wait + 1.0 / 60;
		}
		if (lane1.front()->v.getPosition().x >= 1800)
		{
			Bhan.west_1.lane1.pop();
		}

		lane1.front()->v.move(Vector2f(lane1.front()->speed, 0));
		if ((pre - 5) - (lane1.front()->v.getPosition().x + lane1.front()->v.getSize().x) < lane1.front()->speed * 15)
		{
			lane1.front()->speed = max(0.f,((pre - 5) - (lane1.front()->v.getPosition().x + lane1.front()->v.getSize().x)) / 15);
		}
		else if (lane1.front()->speed < lane1.front()->maxspeed)
		{
			lane1.front()->speed += 1.0 / 15;
		}
		pre = lane1.front()->v.getPosition().x;
		lane1.pop();
	}

	pre = 1900;
	while (!lane2.empty())
	{
		if (lane2.front()->speed <= 1/10)
		{
			wait = wait + 1.0 / 60;
		}
		if (lane2.front()->v.getPosition().x >= 1800)
		{
			Bhan.west_1.lane2.pop();
		}


		lane2.front()->v.move(Vector2f(lane2.front()->speed, 0));
		if ((pre - 5) - (lane2.front()->v.getPosition().x + lane2.front()->v.getSize().x) < lane2.front()->speed * 15)
		{
			lane2.front()->speed = max(0.f,((pre - 5) - (lane2.front()->v.getPosition().x + lane2.front()->v.getSize().x)) / 15);
		}
		else if (lane2.front()->speed < lane2.front()->maxspeed)
		{
			lane2.front()->speed += 1.0 / 15;
		}
		pre = lane2.front()->v.getPosition().x;
		lane2.pop();
	}

	pre = 1900;
	while (!lane3.empty())
	{
		if (lane3.front()->speed <= 1/10)
		{
			wait = wait + 1.0 / 60;
		}
		if (lane3.front()->v.getPosition().x >= 1800)
		{
			Bhan.west_1.lane3.pop();
		}

		

		lane3.front()->v.move(Vector2f(lane3.front()->speed, 0));
		if ((pre - 5) - (lane3.front()->v.getPosition().x + lane3.front()->v.getSize().x) < lane3.front()->speed * 15)
		{
			lane3.front()->speed = max(0.f,((pre - 5) - (lane3.front()->v.getPosition().x + lane3.front()->v.getSize().x)) / 15);
		}
		else if (lane3.front()->speed < lane3.front()->maxspeed)
		{
			lane3.front()->speed += 1.0 / 15;
		}
		pre = lane3.front()->v.getPosition().x;
		lane3.pop();
	}

	



	temp = Bhan.north_1;
	lane1 = temp.lane1;
	lane2 = temp.lane2;
	lane3 = temp.lane3;

	pre = -10;
	while (!lane1.empty())
	{
		if (lane1.front()->speed <= 1/10)
		{
			wait = wait + 1.0 / 60;
		}
		if (lane1.front()->v.getPosition().y <= 0)
		{
			Bhan.north_1.lane1.pop();
		}


		lane1.front()->v.move(Vector2f(0, ( - 1) * (lane1.front()->speed)));
		if ((lane1.front()->v.getPosition().y )- (pre + 5) < lane1.front()->speed * 10)
		{
			lane1.front()->speed = max(0.f,((lane1.front()->v.getPosition().y) - (pre + 5)) / 15);
		}
		else if (lane1.front()->speed < lane1.front()->maxspeed)
		{
			lane1.front()->speed += 1.0 / 15;
		}
		pre = lane1.front()->v.getPosition().y+lane1.front()->v.getSize().y;
		lane1.pop();
	}

	pre = -10;
	while (!lane2.empty())
	{
		if (lane2.front()->speed <= 1/10)
		{
			wait = wait + 1.0 / 60;
		}
		if (lane2.front()->v.getPosition().y <= 0)
		{
			Bhan.north_1.lane2.pop();
		}


		lane2.front()->v.move(Vector2f(0, (lane2.front()->speed)*(-1)));
		if ( (lane2.front()->v.getPosition().y - (pre + 5)) < lane2.front()->speed * 15)
		{
			lane2.front()->speed = max(0.f,( (lane2.front()->v.getPosition().y )- (pre + 5)) / 15);
		}
		else if (lane2.front()->speed < lane2.front()->maxspeed)
		{
			lane2.front()->speed += 1.0 / 15;
		}
		pre = lane2.front()->v.getPosition().y+ lane2.front()->v.getSize().y;
		lane2.pop();
	}
	
}

void draw_intersection(intersection Bhan, RenderWindow& window)
{

	queue<vehicle*> lane1 = Bhan.east.lane1;
	queue<vehicle*> lane2 = Bhan.east.lane2;
	queue<vehicle*> lane3 = Bhan.east.lane3;
	while (!lane1.empty())
	{
		window.draw(lane1.front()->v);
		lane1.pop();
	}
	while (!lane2.empty())
	{
		window.draw(lane2.front()->v);
		lane2.pop();
	}
	while (!lane3.empty())
	{
		window.draw(lane3.front()->v);
		lane3.pop();
	}

	lane1 = Bhan.north.lane1;
	lane2 = Bhan.north.lane2;
	lane3 = Bhan.north.lane3;
	while (!lane1.empty())
	{
		window.draw(lane1.front()->v);
		lane1.pop();
	}
	while (!lane2.empty())
	{
		window.draw(lane2.front()->v);
		lane2.pop();
	}
	while (!lane3.empty())
	{
		window.draw(lane3.front()->v);
		lane3.pop();
	}

	lane1 = Bhan.east_1.lane1;
	lane2 = Bhan.east_1.lane2;
	lane3 = Bhan.east_1.lane3;
	while (!lane1.empty())
	{
		window.draw(lane1.front()->v);
		lane1.pop();
	}
	while (!lane2.empty())
	{
		window.draw(lane2.front()->v);
		lane2.pop();
	}
	while (!lane3.empty())
	{
		window.draw(lane3.front()->v);
		lane3.pop();
	}


	lane1 = Bhan.west.lane1;
	lane2 = Bhan.west.lane2;
	lane3 = Bhan.west.lane3;
	while (!lane1.empty())
	{
		window.draw(lane1.front()->v);
		lane1.pop();
	}
	while (!lane2.empty())
	{
		window.draw(lane2.front()->v);
		lane2.pop();
	}
	while (!lane3.empty())
	{
		window.draw(lane3.front()->v);
		lane3.pop();
	}

	lane1 = Bhan.west_1.lane1;
	lane2 = Bhan.west_1.lane2;
	lane3 = Bhan.west_1.lane3;
	while (!lane1.empty())
	{
		window.draw(lane1.front()->v);
		lane1.pop();
	}
	while (!lane2.empty())
	{
		window.draw(lane2.front()->v);
		lane2.pop();
	}
	while (!lane3.empty())
	{
		window.draw(lane3.front()->v);
		lane3.pop();
	}


	lane1 = Bhan.north_1.lane1;
	lane2 = Bhan.north_1.lane2;
	lane3 = Bhan.north_1.lane3;
	while (!lane1.empty())
	{
		window.draw(lane1.front()->v);
		lane1.pop();
	}
	while (!lane2.empty())
	{
		window.draw(lane2.front()->v);
		lane2.pop();
	}
	while (!lane3.empty())
	{
		window.draw(lane3.front()->v);
		lane3.pop();
	}


}

//getting input from raw data

int day(string date)
{
	string d;
	string m;
	string y;
	char ind = 'd';
	for (int i = 0; i < date.size(); i++)
	{
		if (date[i] == '-')
		{
			if (ind == 'd')
				ind = 'm';
			else if (ind == 'm')
				ind = 'y';
		}
		else if (ind == 'd')
		{
			d.push_back(date[i]);
		}
		else if (ind == 'm')
		{
			m.push_back(date[i]);
		}
		else if (ind == 'y')
		{
			y.push_back(date[i]);
		}
	}
	int num = stoi(d);
	int month = stoi(m);
	int flag = -1;
	if (month == 1)
	{
		flag = num % 7;
	}
	else
	{
		flag = (num + 3) % 7;
	}
	return flag;
}

int seperation()
{
	ifstream in;
	in.open("Randomised-Traffic-Data.csv");
	if (in.fail())
	{
		cout << "in failed";
		return 1;
	}
	ofstream ulu;
	ofstream raj;
	ofstream abc;
	ulu.open("Ulubari.csv");
	if (ulu.fail())
	{
		cout << "ulu failed";
		return 1;
	}
	raj.open("Rajgarh.csv");
	if (raj.fail())
	{
		cout << "raj failed";
		return 1;
	}
	abc.open("ABC.csv");
	if (abc.fail())
	{
		cout << "abc failed";
		return 1;
	}
	ofstream uluh;
	ofstream rajh;
	ofstream abch;
	uluh.open("Ulubari_holidays.csv");
	if (uluh.fail())
	{
		cout << "uluh failed";
		return 1;
	}
	rajh.open("Rajgarh_holidays.csv");
	if (rajh.fail())
	{
		cout << "rajh failed";
		return 1;
	}
	abch.open("ABC_holidays.csv");
	if (abch.fail())
	{
		cout << "abch failed";
		return 1;
	}
	map<string, int> mpp;
	string s;
	getline(in, s);
	string date;
	string stime;
	string etime;
	string approach;
	string two;
	string three, lmv;
	string hcv, lcv;
	string total;
	abc << "date,day,hour,two wheeler,three wheeler,car,hcv,total\n";
	abch << "date,day,hour,two wheeler,three wheeler,car,hcv,total\n";
	ulu << "date,day,hour,two wheeler,three wheeler,car,hcv,total\n";
	uluh << "date,day,hour,two wheeler,three wheeler,car,hcv,total\n";
	raj << "date,day,hour,two wheeler,three wheeler,car,hcv,total\n";
	rajh << "date,day,hour,two wheeler,three wheeler,car,hcv,total\n";
	while (getline(in, s))
	{
		string cell;
		int cnt = 0;
		stringstream k(s);
		while (getline(k, cell, ','))
		{
			cnt++;
			if (cnt == 2)
			{
				date = cell;
			}
			if (cnt == 3)
			{
				stime = cell;
			}
			if (cnt == 4)
			{
				etime = cell;
			}
			if (cnt == 7)
			{
				approach = cell;
			}
			if (cnt == 8)
			{
				two = cell;
			}
			if (cnt == 9)
				three = cell;
			if (cnt == 10)
			{
				hcv = cell;
			}
			if (cnt == 11)
			{
				lcv = cell;
			}
			if (cnt == 12)
			{
				lmv = cell;
			}
			if (cnt == 15)
			{
				total = cell;
			}
		}
		string start;
		int i = 0;
		while (stime[i] != ':')
		{
			start.push_back(stime[i]);
			i++;
		}
		int hour = stoi(start);
		if (hour == 12)
		{
			if (stime[stime.size() - 2] == 'A')
				hour = 0;
		}
		else if (stime[stime.size() - 2] == 'P')
		{
			hour = hour + 12;
		}
		int h = day(date);
		int car = stoi(lmv) + stoi(lcv);
		if (mpp[date] == 1)
		{
			if (approach == "From Ulubari (Bhangagarh Bridge 1)")
			{
				uluh << date << "," << h << "," << hour << "," << two << "," << three << "," << car << "," << hcv << "," << total << "\n";
			}
			if (approach == "From ABC Point (Bhangagarh Bridge 1)")
			{
				abch << date << "," << h << "," << hour << "," << two << "," << three << "," << car << "," << hcv << "," << total << "\n";
			}
			if (approach == "From Rajgarh (Bhangagarh Bridge 1)")
			{
				rajh << date << "," << h << "," << hour << "," << two << "," << three << "," << car << "," << hcv << "," << total << "\n";
			}
		}
		else
		{
			if (approach == "From Ulubari (Bhangagarh Bridge 1)")
			{
				ulu << date << "," << h << "," << hour << "," << two << "," << three << "," << car << "," << hcv << "," << total << "\n";
			}
			if (approach == "From ABC Point (Bhangagarh Bridge 1)")
			{
				abc << date << "," << h << "," << hour << "," << two << "," << three << "," << car << "," << hcv << "," << total << "\n";
			}
			if (approach == "From Rajgarh (Bhangagarh Bridge 1)")
			{
				raj << date << "," << h << "," << hour << "," << two << "," << three << "," << car << "," << hcv << "," << total << "\n";
			}
		}
	}
	abc.close();
	abch.close();
	raj.close();
	rajh.close();
	ulu.close();
	uluh.close();
	in.close();
}

vector<int> extract(string filename, string date, string hour)
{
	fstream abc;
	abc.open(filename);
	if (abc.fail())
	{
		cout << "extract abc failed";
	}
	vector<int> CAR;
	vector<int> TWO;
	vector<int> HCV;
	string s;
	string date_val;
	string hour_val;
	string car;
	string hcv;
	string two;
	while (getline(abc, s))
	{
		stringstream ss(s);
		string cell;
		int cnt = 0;
		while (getline(ss, cell, ','))
		{
			cnt++;
			if (cnt == 1)
			{
				date_val = cell;
			}
			if (cnt == 3)
			{
				hour_val = cell;
			}
			if (cnt == 4)
			{
				two = cell;
			}
			if (cnt == 6)
			{
				car = cell;
			}
			if (cnt == 7)
			{
				hcv = cell;
			}
		}
		if (date_val == date && hour_val == hour)
		{
			CAR.push_back(stoi(car));
			TWO.push_back(stoi(two));
			HCV.push_back(stoi(hcv));
		}
	}
	int csum = 0, tsum = 0, hsum = 0;
	for (int i = 0; i < CAR.size(); i++)
	{
		csum = csum + CAR[i];
		tsum = tsum + TWO[i];
		hsum = hsum + HCV[i];
	}
	vector<int> ans;
	ans.push_back(csum / CAR.size());
	ans.push_back(tsum / CAR.size());
	ans.push_back(hsum / CAR.size());
	ans.push_back(98756);

	return ans;
}

vector<vector<int>> get_volume()
{
	seperation();
	string date;
	cout << "Enter Date (DD-MM-YYYY): ";
	cin >> date;
	string hour;
	cout << "Enter Start Time(0 to 23): ";
	cin >> hour;
	vector<vector<int>> ans;
	vector<int> v = extract("Rajgarh.csv", date, hour);
	ans.push_back(v);
	v = extract("Ulubari.csv", date, hour);
	ans.push_back(v);
	v = extract("ABC.csv", date, hour);
	ans.push_back(v);
	return ans;
}

//Adding Randomness

void Raj_getSequence(vector<pair<int, pair<int, int>>>& v_lmv, vector<pair<int, pair<int, int>>>& v_two, vector<pair<int, pair<int, int>>>& v_hcv, int n,int m,int q,int seed)
{
	//cout << "Rajgarh :" << endl;
	int x = 0, r = 0;
	int arr[] = { 7,11,14,19,22,29,33,34,35,38,41,42,43,44,53,55,56,58,66,68,70,73,82,84,86,88,91,93,95,103,107,110,112,114,127,136,137,142,143,145,146,152,153,155,159,161,164,168,172,173,174,177,182,186,189,190,206,212,220,224,228,232,247,249,253,254,255,257,264,265,272,274,280,283,284,286,290,291,292,297,304,309,310,311,315,317,318,321,327,329,336,337,344,346,347,348,352,354,369,373,377,381,389,395,411,412,415,419,424,427,428,429,433,437,440,442,446,448,449,455,456,458,459,464,465,474,487,489,491,494,498,506,508,510,513,515,517,519,528,531,533,535,543,545,546,548,557,558,559,560,563,566,567,568,572,579,582,587,590,594 };
	int p = arr[seed%159];
	int k=1;
	for (int i = 0; i < n+m+q; i++)
	{
		k = (k * p) % 601;
		//cout << k << " ";
		int l = k;
		if (l % 2 == 0)
		{
			x++;
			pair<int, int> t = { 0,1 };
			if (i < n)
				v_lmv.push_back({ k,t });
			else if (i < n + m)
				v_two.push_back({ k,t });
			else
				v_hcv.push_back({ k,t });
		}
		else if (l % 2 == 1)
		{
			r++;
			pair<int, int> t = { 1,0 };
			if (i < n)
				v_lmv.push_back({ k,t });
			else if (i < n + m)
				v_two.push_back({ k,t });
			else
				v_hcv.push_back({ k,t });
		}
	}
	//cout << "Left: " << x << " Right: " << r << endl;
}

void Ulu_getSequence(vector<pair<int, pair<int, int>>>& v_lmv, vector<pair<int, pair<int, int>>>& v_two, vector<pair<int, pair<int, int>>>& v_hcv, int n, int m, int q, int seed)
{
	int arr[] = { 7,11,14,19,22,29,33,34,35,38,41,42,43,44,53,55,56,58,66,68,70,73,82,84,86,88,91,93,95,103,107,110,112,114,127,136,137,142,143,145,146,152,153,155,159,161,164,168,172,173,174,177,182,186,189,190,206,212,220,224,228,232,247,249,253,254,255,257,264,265,272,274,280,283,284,286,290,291,292,297,304,309,310,311,315,317,318,321,327,329,336,337,344,346,347,348,352,354,369,373,377,381,389,395,411,412,415,419,424,427,428,429,433,437,440,442,446,448,449,455,456,458,459,464,465,474,487,489,491,494,498,506,508,510,513,515,517,519,528,531,533,535,543,545,546,548,557,558,559,560,563,566,567,568,572,579,582,587,590,594 };
	int p = arr[seed % 159];
	cout << p << endl;
	int k = 1;
	int r = 0, x = 0;
	//cout << "Ulubari : " << endl;
	for (int i = 0; i < n + m + q; i++)
	{
		k = (k * p) % 601;
		//cout << k << " ";
		int l = k;
		if (l % 10 <8)
		{
			x++;
			pair<int, int> t;
			if (l % 2 == 0)
				t = { 0,1 };
			else
				t = { 0,0 };
			if (i < n)
				v_lmv.push_back({ k,t });
			else if (i < n + m)
				v_two.push_back({ k,t });
			else
				v_hcv.push_back({ k,t });
		}
		else
		{
			r++;
			pair<int, int> t;
			if (l % 2 == 0)
				t = { 1,1 };
			else
				t = { 1,0 };
			if (i < n)
				v_lmv.push_back({ k,t });
			else if (i < n + m)
				v_two.push_back({ k,t });
			else
				v_hcv.push_back({ k,t });
		}
	}
	//cout << "Left: " << x << " Right: " << r << endl;	
}

void ABC_getSequence(vector<pair<int, pair<int, int>>>& v_lmv, vector<pair<int, pair<int, int>>>& v_two, vector<pair<int, pair<int, int>>>& v_hcv, int n, int m, int q, int seed)
{
	int arr[] = { 7,11,14,19,22,29,33,34,35,38,41,42,43,44,53,55,56,58,66,68,70,73,82,84,86,88,91,93,95,103,107,110,112,114,127,136,137,142,143,145,146,152,153,155,159,161,164,168,172,173,174,177,182,186,189,190,206,212,220,224,228,232,247,249,253,254,255,257,264,265,272,274,280,283,284,286,290,291,292,297,304,309,310,311,315,317,318,321,327,329,336,337,344,346,347,348,352,354,369,373,377,381,389,395,411,412,415,419,424,427,428,429,433,437,440,442,446,448,449,455,456,458,459,464,465,474,487,489,491,494,498,506,508,510,513,515,517,519,528,531,533,535,543,545,546,548,557,558,559,560,563,566,567,568,572,579,582,587,590,594 };
	int p = arr[seed % 159];
	cout << p << endl;
	int k = 1;
	int r = 0, x = 0;
	//cout << "ABC : " << endl;
	for (int i = 0; i < n + m + q; i++)
	{
		k = (k * p) % 601;
		//cout << k << " ";
		int l = k;
		if (l % 10 >= 8)
		{
			l++;
			pair<int, int> t;
			if (l % 2 == 0)
				t = { 0,1 };
			else
				t = { 0,0 };
			if (i < n)
				v_lmv.push_back({ k,t });
			else if (i < n + m)
				v_two.push_back({ k,t });
			else
				v_hcv.push_back({ k,t });
		}
		else
		{
			x++;
			pair<int, int> t;
			if (l % 2 == 0)
				t = { 1,1 };
			else
				t = { 1,0 };
			if (i < n)
				v_lmv.push_back({ k,t });
			else if (i < n + m)
				v_two.push_back({ k,t });
			else
				v_hcv.push_back({ k,t });
		}
	}
	//cout << "Left: " << x << " Right: " << r << endl;
}

//Sorting

void sorting(vector<pair<int, pair<int, int>>>& v)
{
	for (int i = 0; i < v.size(); i++)
	{
		for (int j = 0; j < v.size()-i-1; j++)
		{
			if (v[j].first > v[j + 1].first)
				swap(v[j], v[j + 1]);
		}
	}
}

//Simulation function

int simulate(float Raj_time,float Ulu_time,float ABC_time)
{
	float wait = 0;
	float N_wait = 0;
	float W_wait = 0;
	float E_wait=0;
	vector<vector<int>> g=get_volume();
	for (auto it : g)
	{
		for (auto i : it)
			cout << i << " ";
		cout << endl;
	}
	vector<pair<int, pair<int, int>>> raj_lmv;
	vector<pair<int, pair<int, int>>> raj_two;
	vector<pair<int, pair<int, int>>> raj_hcv;
	
	int n = g[0][0]+1;
	int m = g[0][1]+5;
	int k = g[0][2]+1;
	int seed= 1478;
	
	Raj_getSequence(raj_lmv, raj_two, raj_hcv, n, m/5, k, seed);
	sorting(raj_lmv);
	sorting(raj_hcv);
	sorting(raj_two);
	

	vector<pair<int, pair<int, int>>> ulu_lmv;
	vector<pair<int, pair<int, int>>> ulu_two;
	vector<pair<int, pair<int, int>>> ulu_hcv;
	

	n = g[1][0]+1;
	m = g[1][1]+5;
	k = g[1][2]+1;
	seed = 147856;


	Ulu_getSequence(ulu_lmv, ulu_two, ulu_hcv, n, m / 5, k, seed);
	sorting(ulu_lmv);
	sorting(ulu_hcv);
	sorting(ulu_two);
	


	vector<pair<int, pair<int, int>>> abc_lmv;
	vector<pair<int, pair<int, int>>> abc_two;
	vector<pair<int, pair<int, int>>> abc_hcv;
	n = g[2][0]+1;
	m = g[2][1]+5;
	k = g[2][2]+1;
	seed = 369852;
	ABC_getSequence(abc_lmv, abc_two, abc_hcv, n, m / 5, k, seed);
	sorting(abc_lmv);
	sorting(abc_hcv);
	sorting(abc_two);





	RenderWindow window(VideoMode(1800.f, 950.f), "Traffic simulator");
	window.setFramerateLimit(180);

	Text rajgarh;
	Text ulubari;
	Text abc;

	Font normal;
	normal.loadFromFile("cour.ttf");

	rajgarh.setString("Rajgarh Road");
	rajgarh.setFillColor(Color::Black);
	rajgarh.setCharacterSize(30);
	rajgarh.setOutlineThickness(1);
	rajgarh.setPosition(Vector2f(948.f, 230.f));
	rajgarh.rotate(-90);
	rajgarh.setFont(normal);

	ulubari.setString("Ulubari Road");
	ulubari.setFillColor(Color::Black);
	ulubari.setCharacterSize(30);
	ulubari.setOutlineThickness(1);
	ulubari.setPosition(Vector2f(15.f, 606.f));
	ulubari.setFont(normal);

	abc.setString("ABC-Point Road");
	abc.setFillColor(Color::Black);
	abc.setCharacterSize(30);
	abc.setOutlineThickness(1);
	abc.setPosition(Vector2f(1540.f, 786.f));
	abc.setFont(normal);

	RectangleShape car_legend(Vector2f(15.f,10.f));
	car_legend.setFillColor(Color::White);
	car_legend.setPosition(Vector2f(15.f, 15.f));

	RectangleShape bike_legend(Vector2f(15.f, 10.f));
	bike_legend.setFillColor(Color::Blue);
	bike_legend.setPosition(Vector2f(15.f, 30.f));

	RectangleShape hcv_legend(Vector2f(30.f, 12.f));
	hcv_legend.setFillColor(Color::Red);
	hcv_legend.setPosition(Vector2f(15.f, 45.f));

	Text car_text;
	Text bike_text;
	Text hcv_text;

	car_text.setString("Car");
	car_text.setFillColor(Color::White);
	car_text.setCharacterSize(15);
	car_text.setPosition(Vector2f(49.f,10.f));
	car_text.setFont(normal);


	bike_text.setString("Block of 5 bikes");
	bike_text.setFillColor(Color::White);
	bike_text.setCharacterSize(15);
	bike_text.setPosition(Vector2f(49.f, 24.f));
	bike_text.setFont(normal);

	hcv_text.setString("Heavy vehicle");
	hcv_text.setFillColor(Color::White);
	hcv_text.setCharacterSize(15);
	hcv_text.setPosition(Vector2f(49.f, 42.f));
	hcv_text.setFont(normal);

	RectangleShape back(Vector2f(300, 60));
	back.setPosition(Vector2f(10, 10));
	back.setFillColor(Color::Black);






	RectangleShape EW(Vector2f(1800.f, 132.f));
	EW.setPosition(Vector2f(0.f, 650.f));
	EW.setFillColor(Color::Black);

	RectangleShape NS(Vector2f(88.f, 650.f));
	NS.setPosition(Vector2f(858.f, 0.f));
	NS.setFillColor(Color::Black);

	RectangleShape East_divider(Vector2f(853, 4));
	East_divider.setFillColor(Color::Green);
	East_divider.setPosition(Vector2f(0.f, 714.f));

	RectangleShape West_divider(Vector2f(853, 4));
	West_divider.setFillColor(Color::Green);
	West_divider.setPosition(Vector2f(947.f, 714.f));

	RectangleShape North_divider(Vector2f(4.f, 645.f));
	North_divider.setFillColor(Color::Green);
	North_divider.setPosition(Vector2f(898.f, 0.f));

	CircleShape East_signal_green(12.f);
	East_signal_green.setFillColor(Color(0, 50, 0));
	East_signal_green.setPosition(Vector2f(827.f, 615.f));

	CircleShape East_signal_yellow(12.f);
	East_signal_yellow.setFillColor(Color(50,50,0));
	East_signal_yellow.setPosition(Vector2f(794.f, 615.f));

	CircleShape East_signal_red(12.f);
	East_signal_red.setFillColor(Color::Red);
	East_signal_red.setPosition(Vector2f(761.f, 615.f));

	CircleShape West_signal_green(12.f);
	West_signal_green.setFillColor(Color(0,50,0));
	West_signal_green.setPosition(Vector2f(1013.f, 787.f));

	CircleShape West_signal_yellow(12.f);
	West_signal_yellow.setFillColor(Color(50,50,0));
	West_signal_yellow.setPosition(Vector2f(980.f, 787.f));

	CircleShape West_signal_red(12.f);
	West_signal_red.setFillColor(Color::Red);
	West_signal_red.setPosition(Vector2f(947.f, 787.f));



	CircleShape North_signal_red(12.f);
	North_signal_red.setFillColor(Color(50,0,0));
	North_signal_red.setPosition(Vector2f(947.f, 559.f));

	CircleShape North_signal_yellow(12.f);
	North_signal_yellow.setFillColor(Color(50,50,0));
	North_signal_yellow.setPosition(Vector2f(947.f, 592.f));

	CircleShape North_signal_green(12.f);
	North_signal_green.setFillColor(Color::Green);
	North_signal_green.setPosition(Vector2f(947.f, 625.f));
	intersection Bhan = intersection();


	//window



	int cnt = 0;
	int v_cnt = 0;
	int flag = 0;
	int r_lmv = 0, r_two = 0, r_hcv = 0;
	int u_lmv = 0, u_two = 0, u_hcv = 0;
	int a_lmv = 0, a_two = 0, a_hcv = 0;
	int timer = 0;

	Font f;
	if (!f.loadFromFile("font.TTF"))
	{
		cout << "unable to load";
		return 0;
	}

	while (window.isOpen())
	{
		if (raj_lmv[r_lmv].first * 60 == cnt)
		{
			if (raj_lmv[r_lmv].second.first == 1)
				Bhan.north.add(5, Vector2f(904, 0), 1, 1, 1, "car");
			else
				Bhan.north.add(5, Vector2f(926, 0), -1, 1, 2, "car");
			if (r_lmv < raj_lmv.size() - 1)
				r_lmv++;
		}
		if (raj_two[r_two].first * 60 == cnt)
		{
			if (raj_lmv[r_lmv].second.first == 1)
				Bhan.north.add(5, Vector2f(904, 0), 1, 1, 1, "bike");
			else
				Bhan.north.add(5, Vector2f(926, 0), -1, 1, 2, "bike");
			if (r_two < raj_two.size() - 1)
				r_two++;
		}
		if (raj_hcv[r_hcv].first * 60 == cnt)
		{
			if (raj_lmv[r_lmv].second.first == 1)
				Bhan.north.add(5, Vector2f(904, 0), 1, 1, 1, "hcv");
			else
				Bhan.north.add(5, Vector2f(926, 0), -1, 1, 2, "hcv");
			if (r_hcv < raj_hcv.size() - 1)
				r_hcv++;
		}


		if (ulu_lmv[u_lmv].first * 60 == cnt)
		{
			if (ulu_lmv[u_lmv].second.first == 1)
			{
				if (ulu_lmv[u_lmv].second.second == 1)
				{
					Bhan.east.add(5, Vector2f(0, 697), 0, 0, 3, "car");
				}
				else
				{
					Bhan.east.add(5, Vector2f(0, 675), 0, 0, 2, "car");
				}
			}
			else
			{
				Bhan.east.add(5, Vector2f(0, 653), -1, 0, 1, "car");
			}
			if (u_lmv < ulu_lmv.size() - 1)
				u_lmv++;
		}



		if (ulu_two[u_two].first * 60 == cnt)
		{
			if (ulu_two[u_two].second.first == 1)
			{
				if (ulu_two[u_two].second.second == 1)
				{
					Bhan.east.add(5, Vector2f(0, 697), 0, 0, 3, "bike");
				}
				else
				{
					Bhan.east.add(5, Vector2f(0, 675), 0, 0, 2, "bike");
				}
			}
			else
			{
				Bhan.east.add(5, Vector2f(0, 653), -1, 0, 1, "bike");
			}
			if (u_two < ulu_two.size() - 1)
				u_two++;
		}



		if (ulu_hcv[u_hcv].first * 60 == cnt)
		{
			if (ulu_hcv[u_hcv].second.first == 1)
			{
				if (ulu_hcv[u_hcv].second.second == 1)
				{
					Bhan.east.add(5, Vector2f(0, 697), 0, 0, 3, "hcv");
				}
				else
				{
					Bhan.east.add(5, Vector2f(0, 675), 0, 0, 2, "hcv");
				}
			}
			else
			{
				Bhan.east.add(5, Vector2f(0, 653), -1, 0, 1, "hcv");
			}
			if (u_hcv < ulu_hcv.size() - 1)
				u_hcv++;
		}



		if (abc_lmv[a_lmv].first * 60 == cnt)
		{
			if (abc_lmv[a_lmv].second.first == 1)
			{
				if (abc_lmv[a_lmv].second.second == 1)
				{
					Bhan.west.add(5, Vector2f(1800, 722), 0, 0, 1, "car");
				}
				else
				{
					Bhan.west.add(5, Vector2f(1800, 742), 1, 0, 2, "car");
				}
			}
			else
			{
				if (abc_lmv[a_lmv].second.second == 1)
				{
					Bhan.west.add(5, Vector2f(1800, 742), 0, 0, 2, "car");
				}
				else
				{
					Bhan.west.add(5, Vector2f(1800, 764), 0, 0, 3, "car");
				}
			}
			if (a_lmv < abc_lmv.size() - 1)
				a_lmv++;
		}


		if (abc_two[a_two].first * 60 == cnt)
		{
			if (abc_two[a_two].second.first == 1)
			{
				if (abc_two[a_two].second.second == 1)
				{
					Bhan.west.add(5, Vector2f(1800, 722), 0, 0, 1, "bike");
				}
				else
				{
					Bhan.west.add(5, Vector2f(1800, 742), 1, 0, 2, "bike");
				}
			}
			else
			{
				if (abc_two[a_two].second.second == 1)
				{
					Bhan.west.add(5, Vector2f(1800, 742), 0, 0, 2, "bike");
				}
				else
				{
					Bhan.west.add(5, Vector2f(1800, 764), 0, 0, 3, "bike");
				}
			}
			if (a_two < abc_two.size() - 1)
				a_two++;
		}


		if (abc_hcv[a_hcv].first * 60 == cnt)
		{
			if (abc_hcv[a_hcv].second.first == 1)
			{
				if (abc_hcv[a_hcv].second.second == 1)
				{
					Bhan.west.add(5, Vector2f(1800, 722), 0, 0, 1, "hcv");
				}
				else
				{
					Bhan.west.add(5, Vector2f(1800, 742), 1, 0, 2, "hcv");
				}
			}
			else
			{
				if (abc_hcv[a_hcv].second.second == 1)
				{
					Bhan.west.add(5, Vector2f(1800, 742), 0, 0, 2, "hcv");
				}
				else
				{
					Bhan.west.add(5, Vector2f(1800, 764), 0, 0, 3, "hcv");
				}
			}
			if (a_hcv < abc_hcv.size() - 1)
				a_hcv++;
		}


		cnt++;
		v_cnt++;
		if (v_cnt == 60 * Raj_time)
		{
			Bhan.s_north = 0;
			North_signal_green.setFillColor(Color(0, 50, 0));
			North_signal_red.setFillColor(Color::Red);
			East_signal_red.setFillColor(Color(50, 0, 0));
			East_signal_yellow.setFillColor(Color::Yellow);
		}
		if (v_cnt == 60 * (Raj_time+2))
		{
			Bhan.s_north = 0;
			Bhan.s_east = 1;
			East_signal_yellow.setFillColor(Color(50,50,0));
			East_signal_green.setFillColor(Color::Green);
		}
		if (v_cnt == 60 * (Ulu_time + Raj_time + 2))
		{
			Bhan.s_east = 0;
			East_signal_green.setFillColor(Color(0, 50, 0));
			East_signal_red.setFillColor(Color::Red);
			West_signal_red.setFillColor(Color(50, 0, 0));
			West_signal_yellow.setFillColor(Color::Yellow);
		}
		else if (v_cnt == 60 * (Ulu_time + Raj_time + 4))
		{
			Bhan.s_west = 1;
			Bhan.s_east = 0;
			West_signal_yellow.setFillColor(Color(50, 50, 0));
			West_signal_green.setFillColor(Color::Green);
		}
		if (v_cnt == 60 * (Ulu_time + Raj_time + 4 +ABC_time))
		{
			Bhan.s_west = 0;
			West_signal_green.setFillColor(Color(0, 50, 0));
			West_signal_red.setFillColor(Color::Red);
			North_signal_red.setFillColor(Color(50, 0, 0));
			North_signal_yellow.setFillColor(Color::Yellow);
		}
		else if (v_cnt == 60 * (Ulu_time + Raj_time + 6 + ABC_time))
		{
			Bhan.s_west = 0;
			Bhan.s_north = 1;
			v_cnt = 0;
			North_signal_yellow.setFillColor(Color(50, 50, 0));
			North_signal_green.setFillColor(Color::Green);
		}



		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed())
			{
				window.close();
			}
			if (event.KeyPressed && event.key.code == Keyboard::Escape)
				window.close();
		}
		RectangleShape Nd1(Vector2f(2.f, 8.f));
		Nd1.setFillColor(Color::White);
		Nd1.setPosition(Vector2f(878.f, 0));

		RectangleShape Nd2(Vector2f(2.f, 8.f));
		Nd2.setFillColor(Color::White);
		Nd2.setPosition(Vector2f(922.f, 0));

		RectangleShape Ed1(Vector2f(8.f, 2.f));
		Ed1.setFillColor(Color::White);
		Ed1.setPosition(Vector2f(0.f, 670.f));

		RectangleShape Ed2(Vector2f(8.f, 2.f));
		Ed2.setFillColor(Color::White);
		Ed2.setPosition(Vector2f(0.f, 692.f));

		RectangleShape Ed3(Vector2f(8.f, 2.f));
		Ed3.setFillColor(Color::White);
		Ed3.setPosition(Vector2f(0.f, 738.f));

		RectangleShape Ed4(Vector2f(8.f, 2.f));
		Ed4.setFillColor(Color::White);
		Ed4.setPosition(Vector2f(0.f, 760.f));

		RectangleShape Wd1(Vector2f(8.f, 2.f));
		Wd1.setFillColor(Color::White);
		Wd1.setPosition(Vector2f(1800.f, 670.f));

		RectangleShape Wd2(Vector2f(8.f, 2.f));
		Wd2.setFillColor(Color::White);
		Wd2.setPosition(Vector2f(1800.f, 692.f));

		RectangleShape Wd3(Vector2f(8.f, 2.f));
		Wd3.setFillColor(Color::White);
		Wd3.setPosition(Vector2f(1800.f, 738.f));

		RectangleShape Wd4(Vector2f(8.f, 2.f));
		Wd4.setFillColor(Color::White);
		Wd4.setPosition(Vector2f(1800.f, 760.f));

		//Update

		timer++;
		int minute, sec;
		minute = timer / 3600;
		if (minute == 10)
			window.close();
		sec = (timer % 3600) / 60;
		string time_stamps;
		if (sec / 10 != 0)
			time_stamps = "0" + to_string(minute) + ":" + to_string(sec)+"/10:00";
		else
			time_stamps = "0" + to_string(minute) + ":0" + to_string(sec) +"/10:00";

		Text clock;
		clock.setString(time_stamps);
		clock.setFillColor(Color::Black);
		clock.setCharacterSize(60);
		clock.setPosition(Vector2f(1500.f, 15.f));
		clock.setFont(f);


		Update(Bhan,wait,N_wait,E_wait,W_wait);


		//Draw
		window.clear(Color::White);
		window.draw(back);
		window.draw(car_legend);
		window.draw(bike_legend);
		window.draw(hcv_legend);
		window.draw(car_text);
		window.draw(bike_text);
		window.draw(hcv_text);
		window.draw(rajgarh);
		window.draw(ulubari);
		window.draw(abc);
		window.draw(clock);
		window.draw(EW);
		window.draw(NS);
		window.draw(East_divider);
		window.draw(West_divider);
		window.draw(North_divider);
		window.draw(East_signal_green);
		window.draw(East_signal_red);
		window.draw(East_signal_yellow);
		window.draw(West_signal_green);
		window.draw(West_signal_red);
		window.draw(West_signal_yellow);
		window.draw(North_signal_green);
		window.draw(North_signal_red);
		window.draw(North_signal_yellow);
		for (int i = 0; i < 40; i++)
		{
			window.draw(Nd1);
			window.draw(Nd2);
			Nd1.move(Vector2f(0.f, 16.f));
			Nd2.move(Vector2f(0.f, 16.f));
		}
		for (int i = 0; i < 53; i++)
		{
			window.draw(Ed1);
			window.draw(Ed2);
			window.draw(Ed3);
			window.draw(Ed4);
			Ed1.move(Vector2f(16.f, 0.f));
			Ed2.move(Vector2f(16.f, 0.f));
			Ed3.move(Vector2f(16.f, 0.f));
			Ed4.move(Vector2f(16.f, 0.f));
		}

		for (int i = 0; i < 53; i++)
		{
			window.draw(Wd1);
			window.draw(Wd2);
			window.draw(Wd3);
			window.draw(Wd4);
			Wd1.move(Vector2f(-16.f, 0.f));
			Wd2.move(Vector2f(-16.f, 0.f));
			Wd3.move(Vector2f(-16.f, 0.f));
			Wd4.move(Vector2f(-16.f, 0.f));
		}

		draw_intersection(Bhan, window);

		window.display();
	}
	cout << "Rajgarh waiting time: " << N_wait << endl;
	cout <<"Ulubari waiting time : " << E_wait << endl;
	cout << "ABC waiting time: " << W_wait << endl;
	
	return wait;
}

//Main function

int main()
{
	simulate(10,10,10);
}