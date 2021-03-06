// teris.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"


#include <conio.h>
#include <SFML/Graphics.hpp>
#include<stdlib.h>
#include<stdio.h>
#include <vector>
using namespace std;
using namespace sf;
#include <time.h>


struct point
{
	int x;
	int y;
};

void draw_rect(RenderWindow* window, int x, int y,int colour);
/*
int main()
{
	RenderWindow window(VideoMode (500, 500), "Tetris");
	
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}
		
		window
		
		window.display();
	}
	


	return 0;
}


*/


void draw_rect(RenderWindow* window, int x, int y, int colour)
{
	RectangleShape rectangle(sf::Vector2f(20.f, 20.f));
	rectangle.setPosition(y, x);
	if(colour==1)
	  rectangle.setFillColor(Color::Red);
	if (colour == 2)
		rectangle.setFillColor(Color::Green);
	if (colour == 3)
		rectangle.setFillColor(Color::Blue);
	window->draw(rectangle);
	
}









const int width = 30;
const int hight = 30;




struct cell
{
	int colour;
	int sign;
	int marker;
};

//1-красный, 2-зеленый,3- синий





cell** setup();
cell** put_block(cell** field);
cell** block_pos_update(cell** field, int* pr);
cell** new_block(cell** field);









 cell** setup()
{
	 cell** new_field=new cell*[hight+1];
	 for (int i = 0; i < hight + 1; i++)
		 new_field[i] = new cell[width];


	 for (int i = 0; i < width; i++)
	 {
		 new_field[hight][i].colour = 1;
		 new_field[hight][i].sign = 0;
	 }
	for (int i = 0; i < hight; i++)
		for (int j = 0; j < width; j++)
		{
			new_field[i][j].colour = 0;
			new_field[i][j].sign = 0;
		}
	 new_block(new_field);
	return new_field;

}





 cell** put_block(cell** field)
 {
	 for (int i = 0; i < hight; i++)
		 for (int j = 0; j < width; j++)
			 field[i][j].sign = 0;
	 return field;
 }




 cell** block_pos_update(cell** field, int* pr)
{    //put blocks
	 for (int i = hight-1; i>-1 ; i--)
		 for (int j = 0; j < width; j++)
			 if ((field[i][j].sign) && (field[i + 1][j].colour)&& (!field[i + 1][j].sign))
			 {
				 put_block(field);
				 *pr = 1;
				 return field;
			 }

	 //move blocks
		for (int i = hight - 1; i > -1; i--)
			for (int j = 0; j < width; j++)
				if (field[i][j].sign)
				{
					field[i + 1][j].colour = field[i][j].colour;
					field[i][j].colour = 0;
					field[i + 1][j].sign = 1;
					field[i][j].sign = 0;
					
				}
		*pr = 0;
		return field;
	
}


 void destruct(cell** field)
 {

 }


cell** new_block(cell** field)
{
	//random start pos
	int spos = rand() % (width - 4);

	//random colour
	
	int colour = (rand() % 3) + 1;

	int tp = rand() % 3;

	


		//horizontal line
	if (tp == 0)
		for (int i = spos; i < spos + 4; i++)
		{
			field[0][i].colour = colour;
			field[0][i].sign = 1;
		}
		
	

		//vertical line
		if (tp == 1)
		for (int i = 0; i < 4; i++)
		{
			field[i][spos].colour = colour;
			field[i][spos].sign = 1;
		}
		

		//horizontal lightening
		if (tp == 2)
		{
			field[0][spos].colour = colour;
			field[0][spos].sign = 1;


			field[0][spos + 1].colour = colour;
			field[0][spos + 1].sign = 1;

			field[1][spos + 1].colour = colour;
			field[1][spos + 1].sign = 1;

			field[1][spos + 2].colour = colour;
			field[1][spos + 2].sign = 1;
		}


		//vertical lightening
		if (tp == 3)
		{
			field[0][spos].colour = colour;
			field[0][spos].sign = 1;


			field[1][spos].colour = colour;
			field[1][spos].sign = 1;

			field[1][spos + 1].colour = colour;
			field[1][spos + 1].sign = 1;

			field[2][spos + 1].colour = colour;
			field[2][spos + 1].sign = 1;
		}



	
	return field;
}


















void draw_field(RenderWindow* window, cell** field)
{
	window->clear();
	for (int i = 0; i < hight; i++)
		for (int j = 0; j < width; j++)
			if (field[i][j].colour)
				draw_rect(window, i * 20, j * 20, field[i][j].colour);
	window->display();
}





void move(cell**field,char sym)
{
	
	if (sym == 0)
	{
		for (int i = hight - 1; i > -1; i--)
			for (int j = 0; j < width; j++)
				if (field[i][j].sign)
					if (j)
					{
						field[i][j - 1].sign = 1;
						field[i][j - 1].colour = field[i][j].colour;
						field[i][j].colour = 0;
						field[i][j].sign = 0;
					}

	}

	if (sym==3)
		for (int i = hight - 1; i > -1; i--)
			for (int j = width-1; j >-1; j--)
				if (field[i][j].sign)
					if (j)
					{
						field[i][j + 1].sign = 1;
						field[i][j + 1].colour = field[i][j].colour;
						field[i][j].colour = 0;
						field[i][j].sign = 0;
					}

	if (sym == 4)
		for (int i = hight - 1; i > -1; i--)
			for (int j = width - 1; j > -1; j--)
				if ((field[i][j].sign)&& !(field[i+1][j].sign))
					if (j)
					{
						field[i+1][j].sign = 1;
						field[i+1][j].colour = field[i][j].colour;
						field[i][j].colour = 0;
						field[i][j].sign = 0;
					}



}




bool destroy(cell** field)
{
	bool f = false;

	for (int i = hight-1; i > -1; i--)
		for (int j = 0; j < width-1; j++)
		{
			int c = 0;
			while ((field[i][j].colour == field[i][j + c].colour)&&((j+c)<width-1))
				c++;

			if (field[i][j].colour&&!field[i][j].sign)
				if (c > 7)
				{
					f = true;
					for (int k = 0; k < c; k++)
						field[i][j + k].colour = 0;



					//here also put down,yeah stupid
					for (int k = 0; k < c; k++)
					{
						int n = 1;
						while (field[i - n][j + k].colour)
						{
							field[i - n + 1][j + k].colour = field[i - n][j + k].colour;
							field[i - n][j + k].colour = 0;
							n++;
						}
					}






				}
			c = 0;

		}
	return f;
}





/*
void check_cell(cell** field,int i,int j,int*fl,vector<point> list)
{
	int flg = 0;
	for (auto it = list.begin(); it != list.end(); it++)
		if ((it->x = j) && (it->y == i))
			flg = 1;
	if (!flg)
	{
		point np{ j,i };
		list.push_back(np);

		//down cell
		if ((i < hight - 1) && (field[i + 1][j - 1].colour))
			check_cell(field, i + 1, j, fl,list);

		//left cell
		if ((j) && (field[i][j - 1].colour))
			check_cell(field, i, j - 1, fl,list);
		//right cell 
		if ((j < width - 2) && (field[i][j + 1].colour))
			check_cell(field, i, j + 1, fl,list);
		//up cell
		if ((i) && (field[i - 1][j].colour))
			check_cell(field, i - 1, j, fl,list);
		

	}
	if (i == hight-1)
		*fl = 1;


}



*/
//vector<point> list;
bool Flg;


//void find_bottom(cell** field, int i, int j);

/*void one_more_update(cell** field)
{
	list.clear();
	for (int i = hight - 2; i > 1; i--)
		for (int j = 1; j < width - 1; j++)
		{
			Flg = false;
			if (field[i][j].colour)
				find_bottom(field, i, j);
			if ((!Flg)&& (field[i][j].colour))
			{
				int k = i;
				while ((k < hight - 1)&&(!field[k + 1][j].colour))
				{
		
					field[k + 1][j].colour = field[k][j].colour;
					field[k][j].colour=0;
					k++;
				}
			}
		}
}

*/




int main()
{
	srand(time(NULL));
	int nblock_pr;
	cell** game_field;
	game_field = setup();
	RenderWindow window(VideoMode(600, 600), "Tetris");
	while (window.isOpen()) 
	{
		Event event;
		/*while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}*/
		block_pos_update(game_field, &nblock_pr);
		  if (nblock_pr)
			 new_block(game_field);
		draw_field(&window, game_field);

		while (window.pollEvent(event))
		{
			if (event.type == Event::KeyPressed)
			{
				char a = event.key.code;
				move(game_field, a);
			}
		}

		destroy(game_field);	
		clock_t endwait;
		endwait = clock() + 0.25*CLOCKS_PER_SEC;
		while (clock() < endwait) {}
		
		
	}
	







    
}


// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.





