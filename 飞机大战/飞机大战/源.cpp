#include <iostream>
#include <graphics.h>//easyx
using namespace std;

constexpr auto swidth = 600;
constexpr auto sheigth = 1100;

bool pointinrect(int x, int y, RECT &r)
{
	return (r.left <= x && x <= r.right && r.top <= y && y <= r.bottom);
}

//��ʼ����
void welcome()
{
		LPCTSTR title = _T("�ɻ���ս");
		LPCTSTR tplay = _T("��ʼ��Ϸ");
		LPCTSTR texit = _T("������Ϸ");

		RECT tplayr, texitr;
		BeginBatchDraw();
		setbkcolor(WHITE); // ���ñ�����ɫ
		cleardevice();
		settextstyle(60, 0, _T("����")); //�����ʽ
		settextcolor(BLACK);
		outtextxy(swidth / 2 - textwidth(title) / 2, sheigth/5, title);
		
		settextstyle(40, 0, _T("����")); //�����ʽ
		tplayr.left = swidth / 2 - textwidth(tplay) / 2;
		tplayr.right = tplayr.left + textwidth(tplay);
		tplayr.top = sheigth / 5*3;
		tplayr.bottom = tplayr.top + textheight(tplay);

		texitr.left = swidth / 2 - textwidth(texit) / 2;
		texitr.right = texitr.left + textwidth(texit);
		texitr.top = sheigth / 5*4;
		texitr.bottom = texitr.top + textheight(texit);

		outtextxy(tplayr.left, tplayr.top, tplay);
		outtextxy(texitr.left, texitr.top, texit);

		EndBatchDraw();

		while (1)
		{
				ExMessage mess;
				getmessage(&mess, EX_MOUSE);
				if (mess.lbutton)
				{
					if (pointinrect(mess.x, mess.y, tplayr))
					{
						return;
					}
					else if (pointinrect(mess.x, mess.y, texitr))
					{
						exit(0);
					}
				}
		}
		Sleep(100);
}

//��

class BK // ���� 
{
public:
	BK(IMAGE& img)
		:img(img), y(-sheigth)
	{

	}
	void show()
	{
		if (y == 0) y = -sheigth;
		y += 4;
		putimage(0, y, &img);
	}
private:
	IMAGE& img;
	int y;
};

class Hero
{
public:
	Hero(IMAGE & img)
	:img(img), HP(SHP)
	{
		rect.left = swidth / 2 - img.getwidth() / 2;
		rect.top = sheigth - img.getheight();
		rect.right = rect.left + img.getwidth();
		rect.bottom = sheigth;
	}
	void Show()
	{
		setlinecolor(RED);
		setlinestyle(PS_SOLID, 4);
		putimage(rect.left, rect.top, &img);
		line(rect.left, rect.top - 5, rect.left + (img.getwidth() / SHP * HP), rect.top - 5);
	}
	void Control()
	{
		ExMessage mess;
		if (peekmessage(&mess, EM_MOUSE))
		{
			rect.left = mess.x - img.getwidth() / 2;
			rect.top = mess.y - img.getheight() / 2;
			rect.right = rect.right = rect.left + img.getwidth();
			rect.bottom = rect.top + img.getheight();
		}
	}

	bool hurt()
	{
		HP--;
		return (HP == 0) ? false : true;
	}

	RECT & GetRect() { return rect; }

private:
	IMAGE & img;
	RECT rect;

	unsigned int HP;

};

int play()
{
	setbkcolor(WHITE);
	cleardevice();
	int is_play = 1;

	IMAGE heroimg, enemyimg, bkimg, bulletimg;
	loadimage(&heroimg, _T("C:\\Users\\wyq\\Desktop\\C++����\\ͼƬ\\�Լ��ķɻ�.png"));
	loadimage(&enemyimg, _T("C:\\Users\\wyq\\Desktop\\C++����\\ͼƬ\\�Լ��ķɻ�.png"));
	loadimage(&bkimg, _T("C:\\Users\\wyq\\Desktop\\C++����\\ͼƬ\\����.png"), swidth, sheigth * 2);
	loadimage(&bulletimg, _T("C:\\Users\\wyq\\Desktop\\C++����\\ͼƬ\\�Լ��ķɻ�.png"));

	BK bk = BK(bkimg);

	while (is_play)
	{
		BeginBatchDraw();

		bk.show();
		Sleep(16);

		EndBatchDraw();
	}
	return true;
}

int main()
{
	//easyx�ĳ�ʼ��
	initgraph(swidth, sheigth, EX_NOMINIMIZE | EX_SHOWCONSOLE);
	int is_live = 1;
	while (is_live)
	{
		welcome();
		//play
		is_live = play();
	}

	return 0;
}