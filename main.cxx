#include "graphics.h"
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <sstream>
#include <string>
using namespace std;

class BST_Node
{
public:
	int data;
	BST_Node* left;
	BST_Node* right;

	BST_Node(int data)
	{
		this->data = data;
		left = NULL;
		right = NULL;
	}
};

class BST
{
public:
	BST_Node* Root;

	BST()
	{
		Root = NULL;
	}

	bool IsEmpty()
	{
		if (Root == NULL)
			return true;
		else
			return false;
	}

	BST_Node* Insert(int data, BST_Node* root)
	{
		if (root == NULL)
		{
			BST_Node* NewNode = new BST_Node(data);
			root = NewNode;
			cout << "Insertion Done!" << endl;
			return root;
		}

		if (data < root->data)
		{
			root->left = Insert(data, root->left);
		}
		else if (data > root->data)
		{
			root->right = Insert(data, root->right);
		}
		return root;
	}

	void Insert_Temp(int data)
	{
		Root = Insert(data, Root);
	}

	BST_Node* Search(int data)
	{
		if (IsEmpty())
		{
			return NULL;
		}
		else
		{
			BST_Node* Temp = Root;
			while (Temp != NULL)
			{
				if (data == Temp->data)
				{
					return Temp;
				}
				else if (data < Temp->data)
				{
					Temp = Temp->left;
				}
				else if (data > Temp->data)
				{
					Temp = Temp->right;
				}
			}
		}
		return NULL;
	}


};

class AVL_Node
{
public:
	int data;
	AVL_Node* left;
	AVL_Node* right;
	BST bst_Node;

	AVL_Node(int data)
	{
		this->data = data;
		left = NULL;
		right = NULL;
	}
};

class AVL
{
public:
	AVL_Node* Root;

	AVL()
	{
		Root = NULL;
	}

	AVL_Node* Insertion(int data, AVL_Node* root)
	{
		if (root == NULL)
		{
			AVL_Node* NewNode = new AVL_Node(data);
			root = NewNode;
			return root;
		}
		if (data < root->data)
		{
			root->left = Insertion(data, root->left);
		}
		else if (data > root->data)
		{
			root->right = Insertion(data, root->right);
		}
		return root;
	}

	void Insertion_Temp(int key)
	{
		Root = Insertion(key, Root);
	}


	AVL_Node* Search(int data)
	{
		AVL_Node* Temp = Root;

		if (Temp == NULL)
		{
			return NULL;
		}
		else
		{
			while (Temp != NULL)
			{
				if (data == Temp->data)
				{
					return Temp;
				}
				else if (data < Temp->data)
				{
					Temp = Temp->left;
				}
				else if (data > Temp->data)
				{
					Temp = Temp->right;
				}
			}
		}
		return NULL;
	}

	//private:

	int Tree_Height(AVL_Node* root)
	{
		if (root == NULL)
		{
			return -1;
		}

		int left_height = Tree_Height(root->left);
		int right_height = Tree_Height(root->right);

		if (left_height > right_height)
			return (left_height + 1);
		else
			return (right_height + 1);

	}

	int Balance_Factor(AVL_Node* root)
	{
		if (root == NULL)
		{
			return -1;
		}

		return (Tree_Height(root->left) - Tree_Height(root->right));
	}

	AVL_Node* Left_Rotation(AVL_Node* x)
	{
		AVL_Node* y = x->right;
		AVL_Node* T2 = y->left;

		y->left = x;
		x->right = T2;

		return y;
	}

	AVL_Node* Right_Rotation(AVL_Node* y)
	{
		AVL_Node* x = y->left;
		AVL_Node* T2 = x->right;

		x->right = y;
		y->left = T2;

		return x;
	}

	AVL_Node* Balance_Tree(AVL_Node* root)
	{
		if (root == NULL)
		{
			return root;
		}

		root->left = Balance_Tree(root->left);
		root->right = Balance_Tree(root->right);

		int BF = Balance_Factor(root);

		if (BF == 2 && Balance_Factor(root->left) >= 0)
		{
			//right rotation
			return Right_Rotation(root);
		}
		else if (BF == -2 && Balance_Factor(root->right) <= 0)
		{
			//left rotation
			return Left_Rotation(root);
		}
		else if (BF == 2 && Balance_Factor(root->left) < 0)
		{
			//left-right
			root->left = Left_Rotation(root->left);
			return Right_Rotation(root);
		}
		else if (BF == -2 && Balance_Factor(root->right) > 0)
		{
			//right-left
			root->right = Right_Rotation(root->right);
			return Left_Rotation(root);
		}
		return root;
	}

};

class Hybrid_Chaining_Model
{
public:

	AVL avl_obj;

	void Insert(int data)
	{
		int key = 0;

		key = data % 10;

		AVL_Node* Current_Key = avl_obj.Search(key);

		if (Current_Key == NULL)
		{
			avl_obj.Insertion_Temp(key);
		}
		Current_Key = avl_obj.Search(key);
		Current_Key->bst_Node.Insert_Temp(data);

	}

	void Search(int data)
	{
		int key;

		key = data % 10;

		AVL_Node* Current_Key = avl_obj.Search(key);
		if (Current_Key == NULL)
		{
			cout << "No Data Found!" << endl;
			return;
		}
		else
		{
			if (!Current_Key->bst_Node.Search(data))
			{
				cout << "No Data Found!" << endl;
			}
			else
			{
				cout << "Data Found!" << endl;
			}
		}
	}

	AVL_Node* Search_Key(int key)
	{
		AVL_Node* Current_Key = avl_obj.Search(key);
		if (Current_Key == NULL)
		{
			return NULL;
		}
		else
		{
			return Current_Key;
		}
	}

	BST_Node* Bst_Root(int data)
	{
		int key;
		key = data % 10;
		AVL_Node* Current_Key = avl_obj.Search(key);
		return Current_Key->bst_Node.Root;
	}

	void DisplayAVL()
	{

	}

	void DisplayBST(int key)
	{

	}
};


int input(int x, int y) {
	setfillstyle(EMPTY_FILL, WHITE);
	floodfill(x + 1, y + 1, WHITE);

	x += 5;

	string s;
	char ch;
	int i = 0;

	while (1) {
		outtextxy(x + 100 + i, 70, "_");
		ch = getch();

		if (ch == 13 && s.length() > 0)
		{
			break;
		}
		else if (ch == 8 && i >= 8)
		{
			s.pop_back();
			i -= 20;
			outtextxy(x + 98 + i, 70, "   ");
		}
		else if (ch >= '0' && ch <= '9')
		{
			char n[2];
			n[0] = ch;
			n[1] = '\0';
			outtextxy(x + i + 100, 70, n);
			s += ch;
			i += 20;
		}
	}

	i += 8;
	while (i >= 8)
	{
		i -= 8;
		outtextxy(x + 100 + i, 70, "   ");
	}

	return stoi(s);
}


void Display_Interface()
{
	//initwindow(1920, 768, "Hybrid Chaining Model");

	settextstyle(GOTHIC_FONT, HORIZ_DIR, 3);
	line(1920, 50, 0, 50);
	outtextxy(570, 20, "Hybrid Chaining Model");

	settextstyle(GOTHIC_FONT, HORIZ_DIR, 1);
	outtextxy(10, 70, "Insert ");
	rectangle(100, 65, 200, 90);

	settextstyle(GOTHIC_FONT, HORIZ_DIR, 1);
	outtextxy(220, 70, "Search Key");
	rectangle(385, 65, 485, 90);

	settextstyle(GOTHIC_FONT, HORIZ_DIR, 1);
	outtextxy(500, 70, "Search Value");
	rectangle(685, 65, 785, 90);

	settextstyle(GOTHIC_FONT, HORIZ_DIR, 1);
	outtextxy(1420, 67, "Exit");
	rectangle(1400, 65, 1500, 90);
	line(1920, 102, 0, 102);

}

int Tree_Height(AVL_Node* root)
{
	if (root == NULL)
	{
		return -1;
	}

	int left_height = Tree_Height(root->left);
	int right_height = Tree_Height(root->right);

	if (left_height > right_height)
		return (left_height + 1);
	else
		return (right_height + 1);

}

int Balance_Factor(AVL_Node* root)
{
	if (root == NULL)
	{
		return -1;
	}

	return (Tree_Height(root->left) - Tree_Height(root->right));
}

void Display_AVL(AVL_Node* r, int x, int y, int gap, bool& imbalance)
{
	if (!r)
		return;

	circle(x, y, 25);
	string s = to_string(r->data);

	char ch[5];
	int end = 0;
	for (int i = 0; i < s.length(); i++) {
		ch[i] = s[i];
		end = i;
	}
	ch[++end] = '\0';

	outtextxy(x - 8, y - 8, ch);

	if (r->left)
	{
		setfillstyle(SOLID_FILL, LIGHTGREEN);
		floodfill(x, y, WHITE);
		line(x - 25, y, x - 20 * gap, y + 45);
		Display_AVL(r->left, x - 20 * gap, y + 70, gap - 1, imbalance);
	}
	if (r->right)
	{
		setfillstyle(SOLID_FILL, LIGHTCYAN);
		floodfill(x, y, WHITE);
		line(x + 23, y, x + 15 * gap, y + 50);
		Display_AVL(r->right, x + 15 * gap, y + 75, gap - 2, imbalance);
	}

	if (Balance_Factor(r) > 1 || Balance_Factor(r) < -1 && imbalance == false)
	{
		outtextxy(580, 600, "The Tree Is Imbalanced");
		delay(1000);
		imbalance = true;
	}
}

void Search_AVL(AVL_Node* r, int val) {
	int x = 750, y = 180, g = 10;
	AVL_Node* t = r;
	while (t) {
		if (t->data == val) {

			outtextxy(x + 35, y - 5, "<- Found");

			delay(1500);
			outtextxy(x + 30, y - 2, "               ");
			break;
		}
		else if (val < t->data) {
			x = x - 20 * g;
			y = y + 70;
			g = g - 1;
			t = t->left;
		}
		else {
			x = x + 15 * g;
			y = y + 75;
			g = g - 2;
			t = t->right;
		}
	}
}

void Display_BST(BST_Node* r, int x, int y, int gap)
{
	if (!r) return;

	circle(x, y, 25);
	setfillstyle(SOLID_FILL, LIGHTGREEN);
	floodfill(x, y, WHITE);

	string s = to_string(r->data);

	char ch[5];
	int end = 0;
	for (int i = 0; i < s.length(); i++) {
		ch[i] = s[i];
		end = i;
	}
	ch[++end] = '\0';

	outtextxy(x - 15, y - 8, ch);
	if (r->left)
	{
		line(x - 25, y, x - 20 * gap, y + 45);
		Display_BST(r->left, x - 20 * gap, y + 70, gap - 1);
	}
	if (r->right)
	{
		line(x + 23, y, x + 15 * gap, y + 50);
		Display_BST(r->right, x + 15 * gap, y + 75, gap - 2);
	}
}


void Search_BST(BST_Node* r, int val) {
	int x = 750, y = 180, g = 10;
	BST_Node* t = r;
	while (t)
	{
		if (t->data == val) {

			outtextxy(x + 35, y - 5, "<- Found");
			outtextxy(580, 600, "Value Found SuccessFully!");
			break;
		}
		else if (val < t->data)
		{
			x = x - 20 * g;
			y = y + 70;
			g = g - 1;
			t = t->left;
		}
		else {
			x = x + 15 * g;
			y = y + 75;
			g = g - 2;
			t = t->right;
		}
	}
	if (t == NULL)
	{
		outtextxy(580, 600, "Value Not Found!");
	}
}




void BST_Interface(BST_Node* r, int value, bool search)
{
	cleardevice();
	outtextxy(560, 50, "BINARY SEARCH TREE");
	outtextxy(610, 100, "Exit");
	rectangle(600, 90, 670, 125);

	int x = 750, y = 180;
	int x1, y1;
	Display_BST(r, x, y, 10);
	//search the value

	if (search == true)
	{
		Search_BST(r, value);
	}
	while (true)
	{
		getmouseclick(WM_LBUTTONDOWN, x1, y1);
		if (x1 >= 600 && x1 <= 670 && y1 >= 90 && y1 <= 125) {
			break;
		}
	}
}


void Initial_Screen()
{
	initwindow(1920, 768, "Hybrid Chaining Model");

	settextstyle(GOTHIC_FONT, HORIZ_DIR, 3);
	line(1920, 70, 0, 70);
	outtextxy(447, 20, "- - - - - Hybrid Chaining Model - - - - -");
	line(1920, 122, 0, 122);

	settextstyle(GOTHIC_FONT, HORIZ_DIR, 3);
	outtextxy(525, 90, "Data Structure Final Project");

	settextstyle(GOTHIC_FONT, HORIZ_DIR, 3);
	outtextxy(600, 200, "Sheraaz Mehboob");
	outtextxy(620, 250, "Dawood Usman");

	settextstyle(GOTHIC_FONT, HORIZ_DIR, 1);
	circle(740, 320, 20);
	outtextxy(733, 313, "1");
	settextstyle(GOTHIC_FONT, HORIZ_DIR, 2);
	outtextxy(700, 360, " /      \\");
	settextstyle(GOTHIC_FONT, HORIZ_DIR, 1);
	circle(707, 407, 20); circle(780, 407, 20);
	outtextxy(700, 400, "2"); outtextxy(773, 400, "3");
	settextstyle(GOTHIC_FONT, HORIZ_DIR, 2);
	outtextxy(680, 440, "/    \\    /    \\");
	settextstyle(GOTHIC_FONT, HORIZ_DIR, 1);
	circle(667, 487, 20); circle(725, 487, 20); circle(767, 487, 20); circle(823, 487, 20);
	outtextxy(660, 480, "4"); outtextxy(717, 480, "5"); outtextxy(760, 480, "6"); outtextxy(815, 480, "7");

	int x1 = -1;
	int y1 = -1;

	settextstyle(GOTHIC_FONT, HORIZ_DIR, 1);
	outtextxy(720, 575, "Start");
	rectangle(700, 568, 800, 600);

	while (true)
	{
		getmouseclick(WM_LBUTTONDOWN, x1, y1);
		if (x1 >= 700 && x1 <= 800 && y1 >= 568 && y1 <= 600)  //insert
		{
			break;
		}
	}
	cleardevice();
}




int main()
{
	Hybrid_Chaining_Model obj;
	AVL obj1;
	int gd = DETECT;
	int gm;

	int x = 750, y = 180;

	initwindow(1920, 768, "Hybrid Chaining Model");
	Initial_Screen();
	Display_Interface();
	int x1, y1;


	while (true)
	{
		while (!ismouseclick(WM_LBUTTONDOWN))
		{

		}

		getmouseclick(WM_LBUTTONDOWN, x1, y1);
		if (x1 >= 100 && x1 <= 200 && y1 >= 65 && y1 <= 90)  //insert
		{
			bool imbalance = false;
			int data = input(0, 65);
			obj.Insert(data);
			Display_AVL(obj.avl_obj.Root, x, y, 10, imbalance);

			if (imbalance == true)
			{
				delay(1500);
				obj.avl_obj.Root = obj.avl_obj.Balance_Tree(obj.avl_obj.Root);
				//Display_Interface();
				//Display_AVL(obj.avl_obj.Root, x, y, 10, imbalance);
			}
			cleardevice();
			Display_Interface();
			Display_AVL(obj.avl_obj.Root, x, y, 10, imbalance);
			delay(2000);
			BST_Interface(obj.Bst_Root(data), 0, false);

			//initaize the main screen again
			cleardevice();
			Display_Interface();
			Display_AVL(obj.avl_obj.Root, x, y, 10, imbalance);

		}
		else if (x1 >= 385 && x1 <= 485 && y1 >= 65 && y1 <= 90) //search key
		{
			bool imbalance = false; int data = input(285, 65);
			if (obj.Search_Key(data))
			{
				Search_AVL(obj.avl_obj.Root, data);
				Display_AVL(obj.avl_obj.Root, x, y, 10, imbalance);
			}
			else
			{
				outtextxy(565, 600, "                              ");
				outtextxy(570, 600, "Key Not Found!");
				delay(1500);
				outtextxy(565, 600, "                              ");
			}
		}
		else if (x1 >= 685 && x1 <= 785 && y1 >= 65 && y1 <= 90) //search value
		{
			int data = input(585, 65);
			int key = data % 10;
			if (obj.Search_Key(key))
			{
				Search_AVL(obj.avl_obj.Root, key);

				//display the bst of searched key
				delay(1000);

				BST_Interface(obj.Bst_Root(data), data, true);


				bool imbalance = false;
				cleardevice();
				Display_Interface();
				Display_AVL(obj.avl_obj.Root, x, y, 10, imbalance);

			}
			else
			{
				outtextxy(565, 600, "                              ");
				outtextxy(570, 600, "Key Not Found!");
			}
		} //exit
		else if (x1 >= 1400 && x1 <= 1500 && y1 >= 65 && y1 <= 90)
		{
			return 0;
		}
	}


	closegraph();
	return 0;
}
