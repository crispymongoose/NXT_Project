const int MENUSIZE = 5;
const int MAXDESCRIP = 5;
const int HOLDTIME = 2000;
const int MAXORDERS = 10;
int p = 0;

string items[MENUSIZE], descriptions[MENUSIZE][MAXDESCRIP];
int orders[MAXORDERS][MENUSIZE + 1], orderstrack[MAXORDERS][MENUSIZE + 1];
float price[MENUSIZE];

int quantity(int i)
{
	int j = 1, a = 0;
	nxtDisplayString(0, items[i]);
	while (a == 0)
	{
		nxtDisplayString(1, "    %d",j);
		nxtDisplayString(2, "                 ");
		nxtDisplayString(3, "                 ");
		nxtDisplayString(4, "                 ");
		nxtDisplayString(5, "                 ");

		while (nNxtButtonPressed == -1);
		int button = nNxtButtonPressed;
		while (nNxtButtonPressed != -1);

		if (button == 1)
			j ++;
		else if (button == 2)
	  {
      if (j > 0)
      {
        j --;
      }
    }
		else if (button == 3)
			break;
	}
	return j;
}

int menuscroll()
{
  int a = 0;
  while(a == 0)
	{
		if (p < 0)
			p = MENUSIZE - 1 + p;
	  else if(p > MENUSIZE - 1)
	    p = p - MENUSIZE;

		eraseDisplay();
		nxtDisplayString(0, items[p]);
		for (int j = 0; j < MAXDESCRIP; j++)
			nxtDisplayString(j+1, descriptions[p][j]);

		while (nNxtButtonPressed == -1;
		int button = nNxtButtonPressed;
		time1[0] = 0;
		while (nNxtButtonPressed != -1)
	  {
	   if (button == 3 && time1[0] > HOLDTIME)
	   {
	     return -1;
	   }
	  }
		if (button == 1)
			p ++;
		else if (button == 2)
			p --;
		else
			return p;
	}
}

void menuselect(int & ordernum, int tablenum)
{
  orders[ordernum][MENUSIZE] = tablenum;
  orderstrack[ordernum][MENUSIZE] = tablenum;
	int  i = 0, button, quant;
  p = 0;

	nxtDisplayString(0, "Use arrow keys ");
	nxtDisplayString(1, "to scroll through");
	nxtDisplayString(2, "items. To select");
	nxtDisplayString(3, "item, press");
  nxtDisplayString(4, "middle button.");
  nxtDisplayString(5, "Press and hold");
  nxtDisplayString(6, "to finish.");

	while (nNxtButtonPressed == -1);
	while (nNxtButtonPressed != -1);
	i = menuscroll();
  do
  {
  quant = quantity(i);
  orderstrack[ordernum][i] = quant;
  orders[ordernum][i] = quant;
  i = menuscroll();
  }while (i != -1);
}


void intarray()
{
	for (int i = 0; i < MAXORDERS; i++)
	{
		for (int j = 0; j < MENUSIZE; j++)
	  {
			orders[i][j] = 0;
	    orderstrack[i][j] = 0;
	  }
	}
}

int tablereturn(int i)
{
  for(int j = 0; j < MAXORDERS; j++)
  {
    if(orderstrack[j][i] > 0)
    {
      orderstrack[j][i]--;
      return orderstrack[j][MENUSIZE];
    }
  }
  eraseDisplay();
  nxtDisplayString(0, "Dish Not Required");
  while (nNxtButtonPressed == -1);
	while (nNxtButtonPressed != -1);
  return -1;
}

void billDisplay(int ordernum)
{
    nxtDisplayString (0, "Table %d", orders[ordernum][MENUSIZE]);
    int linenum = 1;
    float totalCost = 0;
    for (int i = 0; i < MENUSIZE; i++)
    {
        if (orders[ordernum][i] != 0)
        {
            nxtDisplayString (linenum, "%d %s .. $%3.2f", orders[ordernum][i], items[i], orders[ordernum][i]*price[i]);
            linenum++;
            totalCost += orders[ordernum][i]*price[i];
        }
    }
    nxtDisplayString (linenum, "SUBTOTAL .. $%3.2f", totalCost);
    nxtDisplayString (linenum + 1, "TOTAL .. $%3.2f", totalCost*1.13);
    while (nNxtButtonPressed != -1);
    while (nNxtButtonPressed == -1);
    while (nNxtButtonPressed != -1);
}


task main()
{
  int ordernum = 0, table = 1, a, b, c;

	intarray();
	items[0] = "PASTA";
	items[1] = "SALAD";
	items[2] = "SOUP";
	items[3] = "SANDWICH";
	items[4] = "CAKE";

	price[0] = 1.0;
	price[1] = 2.0;
	price[2] = 3.0;
	price[3] = 4.0;
	price[4] = 5.0;


	descriptions[0][0] = "Penne/spaghetti  ";
	descriptions[0][1] = "and meat sauce";
	descriptions[1][0] = "Fresh greens with";
	descriptions[1][1] = "dressing";
	descriptions[2][0] = "Tomato soup with";
	descriptions[2][1] = "bread sticks";
	descriptions[3][0] = "Cold cuts,";
	descriptions[3][1] = "cheese, and";
	descriptions[3][2] = "lettuce between";
	descriptions[3][3] = "slices of bread";
	descriptions[4][0] = "Warm vanilla";
	descriptions[4][1] = "cake with";
	descriptions[4][2] = "strawberry";
	descriptions[4][3] = "frosting";

	menuselect(ordernum, table);
	while (nNxtButtonPressed != -1);
	eraseDisplay();
	p = 0;
	a = tablereturn(menuscroll());
	while (nNxtButtonPressed != -1);
	eraseDisplay();
	nxtDisplayString(0,"%d",a);
	while (nNxtButtonPressed == -1);
	while (nNxtButtonPressed != -1);
	billDisplay(ordernum);

}
