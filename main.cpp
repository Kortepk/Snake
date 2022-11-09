#include <SFML/Graphics.hpp>  //Библиотека для отрисовки
#include <iostream>
#include <random>

#include "windows.h"

#define SZ 50
#define ASZ 35

using namespace sf;  //Подключение пространство имён sf (чтобы не писать sf::)
using namespace std;

int WIDTH = 1920, HEIGHT = 1080;
float DELTA = 3;

int LEN = 1, SPEED = 0;
char BUT = 'd';	

bool R = false;

Event event; 

Color GetRainbow(int x){
	x %= 1530; //ограничиваем
	
	int layer = x/255; // узнаём какой сектор
	
	x %= 255; // делаем до цветового диапазона
	
	switch(layer){
		case 0:{
			return Color(255, x, 0);
		}
		case 1:{
			return Color(255 - x, 255, 0);
		}
		case 2:{
			return Color(0, 255, x);
		}
		case 3:{
			return Color(0, 255 - x, 255);
		}
		case 4:{
			return Color(x, 0, 255);
		}
		case 5:{
			return Color(255, 0, 255-x);
		}
	}
}

class Body{
	public:
		Vector2i cord;
		RenderWindow snake; // 120x50 
		Body();
		Color clr = Color::Green;
		void run();
		void close();
		void crt(int x);
		void SetPos(Vector2i ps);
		void SetCl(int x);
		Vector2i GetPos();
};

Body::Body(){
	
}

void Body::crt(int x){
	snake.create(VideoMode(SZ, SZ), "Body snake", Style::None);
	//cord = Vector2i(0, 0);
	clr = GetRainbow(x);
		
	snake.clear(clr); 
	snake.setVisible(false);
	snake.display(); 
}

void Body::SetPos(Vector2i ps){
	cord = ps;
}

Vector2i Body::GetPos(){
	return cord;
}

void Body::run(){
	snake.setVisible(true);
	while (snake.pollEvent(event))  
	{		
		if(event.type == Event::KeyPressed){	
				switch(event.key.code){
					case 0:{
						if(BUT != 'd')
							BUT = 'a';
						break;
					}
					case 3:{	
						if(BUT != 'a')			
							BUT = 'd';
						break;
					}
					case 22:{
						if(BUT != 's')
							BUT = 'w';
						break;
					}
					case 18:{
						if(BUT != 'w')
							BUT = 's';
						break;
					}
					case 17:{
						R = !R;
						break;
					}
				}
				
			}
		}
	if(R)
		snake.clear(clr); 
	else
		snake.clear(Color::Green);
		
	snake.setPosition(cord);
	snake.display(); 
} //

void Body::close(){
	snake.close();
}

int main()
{	
	Sleep(2500);

	srand(time(0));
	
	Body bd[100];
	bd[0].crt(510);
	
	RenderWindow apple(VideoMode(ASZ, ASZ), "Apple", Style::None);
	apple.clear(Color::Red);
	
	int x = rand(), y = rand();
	//cout<<x%(WIDTH-ASZ)<<" "<<y%(HEIGHT-40-ASZ)<<"\n";
	Vector2i cord_apple = Vector2i(x%(WIDTH-ASZ), y%(HEIGHT-40-ASZ));
	Vector2i cord_head = Vector2i(1920/2, 1080/2);
	
	apple.setPosition(cord_apple);
	
	RenderWindow head(VideoMode(SZ, SZ), "Snake head", Style::None); // 120x50 
	head.setFramerateLimit(120);
	
	head.setPosition(cord_head);
	
	//LEN = 9;
	for(int i=1; i<LEN; i++)
		bd[i].crt((LEN-1)*64 + 510);
	
	SPEED = DELTA + LEN;
	cout<<"Length snake:\n"<<LEN+1<<"\n";
		
	while (head.isOpen())  
	{		
		while (head.pollEvent(event))  
		{
			if (event.type == Event::Closed)  
				head.close();  
				
			if(event.type == Event::KeyPressed){	
				//cout<<event.key.code<<"\n";
				switch(event.key.code){
					case 0:{
						//cord.x -= 60;
						if(BUT != 'd')
							BUT = 'a';
						break;
					}
					case 3:{
						//cord.x += 60;			
						if(BUT != 'a')			
							BUT = 'd';
						break;
					}
					case 22:{
						//cord.y -= 25;
						if(BUT != 's')
							BUT = 'w';
						break;
					}
					case 18:{
						//cord.y += 25;
						if(BUT != 'w')
							BUT = 's';
						break;
					}
					case 17:{
						R = !R;
						break;
					}
				}
				
			}
		}
		
		while (apple.pollEvent(event))  
		{		
		if(event.type == Event::KeyPressed){
				switch(event.key.code){
					case 0:{
						if(BUT != 'd')
							BUT = 'a';
						break;
					}
					case 3:{	
						if(BUT != 'a')			
							BUT = 'd';
						break;
					}
					case 22:{
						if(BUT != 's')
							BUT = 'w';
						break;
					}
					case 18:{
						if(BUT != 'w')
							BUT = 's';
						break;
					}
					case 17:{
						R = !R;
						break;
					}
				}
				
			}
		}
		
		if(cord_head.x > WIDTH-SZ or cord_head.x < 0 or cord_head.y > HEIGHT-40-SZ or cord_head.y < 0)
			head.close();
		//cout<<but<<" "<<'d'<<"\n";
		
		for(int i=LEN-1; i>0;i--){
			bd[i].SetPos(bd[i-1].GetPos());				
			bd[i].run();
		}	
		bd[0].SetPos(cord_head);
				
		switch(BUT){
			case 'a':{
				cord_head.x -= SPEED;
				head.setPosition(cord_head);
				break;
			}
			case 'd':{
				cord_head.x += SPEED;	
				head.setPosition(cord_head);
				break;
			}
			case 'w':{
				cord_head.y -= SPEED;
				head.setPosition(cord_head);
				break;
			}
			case 's':{
				cord_head.y += SPEED;	
				head.setPosition(cord_head);
				break;
			}
		}
		
		bd[0].run();
		
		bool f1 = (cord_apple.x < cord_head.x and cord_apple.x + ASZ > cord_head.x) or (cord_apple.x < cord_head.x + SZ and cord_apple.x + ASZ > cord_head.x + SZ) ,
		 f2 = ((cord_apple.y < cord_head.y and cord_apple.y + ASZ > cord_head.y) or (cord_apple.y < cord_head.y + SZ and cord_apple.y + ASZ > cord_head.y + SZ)) ,
		 f3 = cord_head.x < cord_apple.x and cord_apple.x + ASZ < cord_head.x + SZ ,
		 f4 = (cord_head.y < cord_apple.y and cord_apple.y + ASZ < cord_head.y + SZ);
		//cout<<f1<<" "<<f2<<" "<<f3<<" "<<f4<<"\n";
		if( (f1 and f2) or ((f3 and f2) or (f4 and f1)) )
		{
			x = rand(), y = rand();
			cord_apple = Vector2i(x%(WIDTH-ASZ-2*SPEED) + SPEED, y%(HEIGHT-40-ASZ-2*SPEED) + SPEED);
			apple.setPosition(cord_apple);
			LEN += 1;
			if(LEN == 101){
				head.close();
				cout<<"\n[You winner!]";
				break;
			}
			bd[LEN-1].crt((LEN-1)*64 + 510);
			
			SPEED = DELTA + LEN;
			cout<<LEN+1<<"\n"; 
		}
		
		if(R)
			apple.clear(GetRainbow((LEN-1)*64 + 510));
		else
			apple.clear(Color::Red);
			
		head.clear(Color::Green); 
		
		apple.display();
		head.display(); 
	}
	cout<<"Game over";
	//system("shutdown -r -t 7");
	return 0;
}