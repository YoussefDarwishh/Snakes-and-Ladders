#include "Output.h"
#include<iostream>
#include "Input.h"
using namespace std;
////////////////////////////////////////////////////////////////////////////////////////// 

Output::Output()
{
	// Initialize user interface parameters
	UI.InterfaceMode = MODE_DESIGN;

	// Widths and Heights

	UI.StatusBarHeight = 60;
	UI.ToolBarHeight = 55;
	UI.MenuItemWidth = 55;

	UI.width = 1210; // make it divisible by NumHorizontalCells
	UI.height = 610; 
	UI.wx = 5;
	UI.wy = 5;

	UI.CellWidth = UI.width / NumHorizontalCells;
	UI.CellHeight = (UI.height -  UI.ToolBarHeight - UI.StatusBarHeight) / NumVerticalCells;

	// Pen Colors of messages of status bar and Players' info
	UI.MsgColor = DARKRED;
	UI.PlayerInfoColor = DARKSLATEBLUE;

	// Background Colors of toolbar and statusbar 
	UI.ToolBarColor = WHITE;
	UI.StatusBarColor = LIGHTGRAY; 

	// Line Colors of the borders of each Cell
	UI.GridLineColor = WHITE;

	// Cell Color if Empty & Cell Number Font & Color
	UI.CellColor_NoCard = BROWN;
	UI.CellNumFont = 13;
	UI.CellNumColor = UI.GridLineColor;

	// Cell Color if Has Card & CARD Number Font & Color
	UI.CellColor_HasCard = VIOLET;
	UI.CardNumFont = 35;
	UI.CardNumColor = WHITE;

	// Ladder Line Width and Color
	UI.LadderlineWidth = 6;
	UI.LadderColor = TURQUOISE;

	// The X and Y Offsets of the Space BEFORE Drawing the Ladder (offset from the start X and Y of the Cell)
	UI.LadderXOffset = (UI.CellWidth  - 2 * UI.LadderlineWidth) / 5;
	UI.LadderYOffset = UI.CellHeight / 2;

	// Snake Line Width and Color
	UI.SnakelineWidth = 6;
	UI.SnakeColor = GREEN;

	// Colors of the 4 Players
	UI.PlayerColors[0] = GOLD;
	UI.PlayerColors[1] = DARKSLATEBLUE;
	UI.PlayerColors[2] = BLACK;
	UI.PlayerColors[3] = GREENYELLOW;

	// Create the output window
	pWind = CreateWind(UI.width + 15, UI.height, UI.wx, UI.wy); 

	// Change the title
	pWind->ChangeTitle("Snakes & Ladders");

	// Create the toolbar, grid area and status bar
	CreateDesignModeToolBar();
	ClearGridArea();
	ClearStatusBar();

}

////////////////////////////////////////////////////////////////////////////////////////// 

window* Output::CreateWind(int w, int h, int x, int y) const
{ 
	// The Window Object is created inside the Ouput class
	window* pW = new window(w, h, x, y);
	return pW;
}

////////////////////////////////////////////////////////////////////////////////////////// 

Input* Output::CreateInput() const
{
	// The Input Object is created inside the Output class
	Input* pIn = new Input(pWind);
	return pIn;
}

//======================================================================================//
//								Some Utility Functions										//
//======================================================================================//

int Output::GetCellStartX(const CellPosition & CellPos) const
{
	///TODO: implement the following function as described in Output.h file
	int X_coordinate;

	X_coordinate = UI.CellWidth*CellPos.HCell();

	return X_coordinate; // this line should be changed with your implementation
}


//////////////////////////////////////////////////////////////////////////////////////////

int Output::GetCellStartY(const CellPosition & CellPos) const
{
	///TODO: implement the following function as described in Output.h file
	int Y_coordinate;
	Y_coordinate = UI.CellHeight*(1+CellPos.VCell());//mistake
	return Y_coordinate; // this line should be changed with your implementation
}
//////////////////////////////////////////////////////////////////////////////////////////

void Output::DrawCardNumber(const CellPosition & CellPos, int CardNum) const
{
	// Get the X and Y of the upper left corner of the Cell
	int CellStartX = GetCellStartX(CellPos);
	int CellStartY = GetCellStartY(CellPos);
	// Set the pen and font
	pWind->SetPen(UI.CardNumColor);
	pWind->SetFont(UI.CardNumFont, BOLD | ITALICIZED , BY_NAME, "Arial");

	int w=0, h=0;


	///TODO: Calculate the Width & Height of the integer "CardNum" if written using the Current Font
	//       (Use GetIntegerSize() window function) and set the "w" and "h" variables with its width and height

	  pWind->GetIntegerSize(w,h,CardNum);

	// Calculate where to write the integer of the CardNum
	int x = CellStartX + UI.CellWidth - UI.LadderXOffset - w - 5; // Before the End vertical line of a ladder 
	                                                              // (assuMinimumg the case where ladder is inside the Cell)
	int y = CellStartY + (UI.CellHeight - h) / 2;	// in the vertical Middle of the Cell


	///TODO: Draw the Integer the representing the "CardNum" in the location (x,y)
	pWind->DrawInteger(x, y, CardNum);


}

//////////////////////////////////////////////////////////////////////////////////////////

void Output::ClearToolBar() const
{
	// Clear by drawing a rectangle filled with toolbar background color
	pWind->SetPen(UI.ToolBarColor, 1);
	pWind->SetBrush(UI.ToolBarColor);
	pWind->DrawRectangle(0, 0, UI.width, UI.ToolBarHeight);
}

//======================================================================================//
//								Interface Functions										//
//======================================================================================//

void Output::ClearStatusBar() const
{
	// Clear drawing a rectangle filled with statusbar background color
	pWind->SetPen(UI.StatusBarColor, 1);
	pWind->SetBrush(UI.StatusBarColor);
	pWind->DrawRectangle(0, UI.height - UI.StatusBarHeight, UI.width, UI.height);
}

//////////////////////////////////////////////////////////////////////////////////////////

void Output::ClearGridArea() const
{
	// Draw each Cell in the Grid: ( NumVerticalCells * NumberHorizontalCells )
	for (int i = 0; i < NumVerticalCells; i++)
	{
		for (int j = 0; j < NumHorizontalCells; j++) 
		{
			CellPosition CellPos(i, j);
			DrawCell(CellPos); // Initially NO Cards in the Cell
		}
	}

 }

//////////////////////////////////////////////////////////////////////////////////////////

void Output::CreateDesignModeToolBar() const
{
	UI.InterfaceMode = MODE_DESIGN;

	ClearToolBar(); // in order not to draw above the icons of the other mode when you switch

	// You can draw the tool bar icons in any way you want.
	// Below is one Positionsible way

	// First prepare List of images for each menu item
	// To control the order of these images in the menu, 
	// reoder them in UI_Info.h ==> enum DESIGN_MODE_ITEMS
	// * MAKE SURE THAT THE IMAGES ARE .JPG FILES *
	string MenuItemImages[DESIGN_ITM_COUNT];
	MenuItemImages[ITM_ADD_LADDER] = "images\\Menu_Ladder.jpg";	
	MenuItemImages[ITM_ADD_SNAKE] = "images\\Menu_Snake.jpg";	
	MenuItemImages[ITM_ADD_CARD] = "images\\Menu_Card.jpg";	
	MenuItemImages[ITM_EXIT] = "images\\Menu_Exit.jpg";
	MenuItemImages[ITM_SWITCH_TO_PLAY_MODE] = "images\\Menu_SwitchToGame.jpg";

	///TODO: Prepare images for each menu item and add it to the list
	MenuItemImages[ITM_COPY_CARD] = "images\\Copy.jpg";	
	MenuItemImages[ITM_CUT_CARD] = "images\\Cut.jpg";	
	MenuItemImages[ITM_PASTE_CARD] = "images\\Paste.jpg";	
	MenuItemImages[ITM_DELETEGAMEOBJECT] = "images\\Delete.jpg";
	MenuItemImages[ITM_SAVEGRID] = "images\\Save.jpg";
	MenuItemImages[ITM_OPENGRID] = "images\\Open.jpg";

	// Draw menu item one image at a time
	for(int i=0; i < DESIGN_ITM_COUNT; i++)
		pWind->DrawImage(MenuItemImages[i], i*UI.MenuItemWidth, 0, UI.MenuItemWidth, UI.ToolBarHeight);


}

//////////////////////////////////////////////////////////////////////////////////////////

void Output::removeLadder(const CellPosition & CellStart ,const CellPosition & CellEnd) const
{
	cout<<"output remove";
} 


void Output::CreatePlayModeToolBar() const
{
	UI.InterfaceMode = MODE_PLAY;

	ClearToolBar(); // in order not to draw above the icons of the other mode when you switch

	// You can draw the tool bar icons in any way you want.
	// Below is one Positionsible way

	// First prepare List of images for each menu item
	// To control the order of these images in the menu, 
	// reoder them in UI_Info.h ==> enum DESIGN_MODE_ITEMS
	// * MAKE SURE THAT THE IMAGES ARE .JPG FILES *
	string MenuItemImages[PLAY_ITM_COUNT];
	MenuItemImages[ITM_ROLL_DICE] = "images\\Menu_Dice.jpg";
	MenuItemImages[ITM_New_Game] = "images\\New_Game.jpg";
	MenuItemImages[ITM_SWITCH_TO_DESIGN_MODE] = "images\\Menu_SwitchToGrid.jpg";

	///TODO: Prepare images for each menu item and add it to the list
	MenuItemImages[ITM_Input_Dice_Value]= "images\\ITM_Input_Dice_Value.jpg";
	
	MenuItemImages[ITM_Menu_Exit]= "images\\Menu_Exit.jpg";

	// Draw menu item one image at a time
	for(int i=0; i < PLAY_ITM_COUNT; i++)
		pWind->DrawImage(MenuItemImages[i], i*UI.MenuItemWidth, 0, UI.MenuItemWidth, UI.ToolBarHeight);

}

//////////////////////////////////////////////////////////////////////////////////////////

void Output::PrintMessage(string msg) const	//Prints a message on status bar
{
	ClearStatusBar();	// First clear the status bar from any previous writing

	// Set pen and font before drawing the string on the window
	pWind->SetPen(UI.MsgColor);
	pWind->SetFont(18, BOLD , BY_NAME, "Verdana");   
	pWind->DrawString(10, UI.height - (int)(UI.StatusBarHeight/1.3), msg);
}

//////////////////////////////////////////////////////////////////////////////////////////

void Output::PrintPlayersInfo(string info)
{
	///TODO: Clear what was written on the toolbar
	CreatePlayModeToolBar();
	// One of the correct ways to implement the above TODO is to call CreatePlayModeToolBar(); 
	// to clear what was written in the Player info (there are other ways too – You are free to use any)

	// Set the pen and font before drawing the string on the window
	pWind->SetPen(UI.PlayerInfoColor); 
	pWind->SetFont(20, BOLD , BY_NAME, "Verdana");   

	int w=0, h=0;

	///TODO: Calculate the Width and Height of the string if drawn using the Current font 
	//       (Use GetStringSize() window function) and set the "w" and "h" variables with its width and height
	pWind->GetStringSize(w,h,info);

	// Set the start X & Y coordinate of drawing the string
	int x = UI.width - w - 20; // space 20 before the right-side of the window
	                           // ( - w ) because x is the coordinate of the start point of the string (upper left)
	int y = (UI.ToolBarHeight - h) / 2; // in the Middle of the toolbar height

	///TODO: Draw the string "info" in the specified location (x, y)

	pWind->DrawString(x, y,info );

}

//======================================================================================//
//			         			Game Drawing Functions   								//
//======================================================================================//

void Output::DrawCell(const CellPosition & CellPos, int CardNum) const
{
	// Get the Cell Number (from 1 to NumVerticalCells*NumHorizontalCells) and the X & Y of its upper left corner
	int CellNum = CellPos.GetCellNum();
	int CellStartX = GetCellStartX(CellPos);
	int CellStartY = GetCellStartY(CellPos);

	// ----- 1- Draw the Cell itself (background) --> Filled Rectangle -----
	pWind->SetPen(UI.GridLineColor, 1);
	if (CardNum == -1) // no Card
		pWind->SetBrush(UI.CellColor_NoCard);
	else
		pWind->SetBrush(UI.CellColor_HasCard);

	///TODO: Draw the Cell Rectangle using the appropriate coordinates
	int CellEndX=UI.CellWidth+CellStartX;
	int CellEndY=UI.CellHeight+CellStartY;
    pWind-> DrawRectangle(CellStartX, CellStartY,CellEndX,CellEndY, FILLED, 0, 0);

	// ----- 2- Draw the CELL number (the small number at the bottom right of the Cell) -----
	pWind->SetPen(UI.CellNumColor);
	pWind->SetFont(UI.CellNumFont, BOLD , BY_NAME, "Verdana");   

	int w=0, h=0;

	///TODO: Get the Width and Height of the Cell Number if written using the Current font 
	//       (Use GetIntegerSize() window function) and set the "w" and "h" variables with its width and height

	pWind->GetIntegerSize(w,h,CellNum);
	


	// Calculate X & Y coordinate of the start point of writing the Card number (upper left point of the Cell num)
	int x = CellStartX + (UI.CellWidth - w - 1);   // space 1 from the end of the Cell width
												   // ( - w ) because x is for the start point of Cell num (num's left corner)
	int y = CellStartY + (UI.CellHeight - h - 1);  // space 1 from the end of the Cell height
											   // ( - w ) because y is for the start point of Cell num (num's upper corner)
	
	///TODO: Draw the Cell number in the x and y location

	pWind->DrawInteger(x, y, CellNum);

	// ----- 3- Draw Card number (if any) -----
	if (CardNum != -1) // Note: CardNum -1 means no Card
		DrawCardNumber(CellPos, CardNum);
}

//////////////////////////////////////////////////////////////////////////////////////////

void Output::DrawPlayer(const CellPosition & CellPos, int PlayerNum, color PlayerColor) const
{

	///TODO: Validate the PlayerNum, if not Valid return
	if (PlayerNum<0||PlayerNum>3)
	{
	
	return ;
	}
	

	// Get the X & Y coordinates of the start point of the Cell (its upper left corner)
	int CellStartX = GetCellStartX(CellPos);
	int CellStartY = GetCellStartY(CellPos);

	// Calculate the Radius of the Player's Circle
	int radius = UI.CellWidth / 14; // proportional to Cell width

	// Calculate the horizontal space before drawing Players circles (space from the left border of the Cell)
	int ySpace = UI.CellHeight / 6; // proportional to Cell height

	// Note: Players' Circles Locations depending on "PlayerNum" is as follows:
	// Player_0   Player_1
	// Player_2   Player_3

	// Calculate the Y coordinate of the center of the Player's circle (based on PlayerNum)
	int y = CellStartY + ySpace + radius + 2;
	if (PlayerNum == 2 || PlayerNum == 3)
		y += radius + 2 + radius; // because PlayerNum 2 and 3 are drawn in the second row of circles

	// Calculate the Y coordinate of the center of the Player's circle (based on PlayerNum)
	int x = CellStartX + UI.LadderXOffset + radius + 4; // UI.LadderXOffset is used to draw Players' circles 
														// AFTER the ladder start vertical line (assuMinimumg there is a ladder)
													    // for not overlapping with ladders
	if (PlayerNum == 1 || PlayerNum == 3)
		x += radius + 2 + radius; // because PlayerNum 1 and 3 are drawn in the second column of circles

	///TODO: Draw the Player circle in center(x,y) and filled with the PlayerColor passed to the function
	pWind->SetBrush(PlayerColor);
	pWind->SetPen(PlayerColor);
	pWind->DrawCircle(x, y, radius, FILLED);
	
}

//////////////////////////////////////////////////////////////////////////////////////////

void Output::DrawLadder(const CellPosition & fromCell, const CellPosition & toCell) const
{

	///TODO: Validate the Cell Position (Must be Vertical Cell AND toCell above fromCell, otherwise, Do NOT draw)
	cout<<"Ladder v Cell value: " << fromCell.VCell() << " " << toCell.VCell()<< endl;
	cout<<"Ladder H Cell value: " << fromCell.HCell() << " " << toCell.HCell()<< endl;
if ((fromCell.VCell()<=toCell.VCell())||(fromCell.HCell()!=toCell.HCell()))
{
	return ;
	}
	
	// Get the start X and Y coordinates of the upper left corner of the fromCell
	int CellStartX = GetCellStartX(fromCell);
	int fromStartY = GetCellStartY(fromCell);

	// Get the start Y coordinates of the upper left corner of the toCell (the X should be the same as fromCell .. Vertical)
	int toStartY = GetCellStartY(toCell);

	// ---- 1- Draw the First Vertical Line ---- 
	int x12 = CellStartX + UI.LadderXOffset; // the two points have the same x (vertical)
	int y1 = fromStartY + UI.LadderYOffset;  // the coordinate y of the first point of the First Vertical line
	int y2 = toStartY + UI.CellHeight - UI.LadderYOffset; // the coordinate y of the second point of the First Vertical line

	///TODO: Set pen color and width using the appropriate parameters of UI_Info object (UI)
	pWind->SetPen(UI.LadderColor,UI.LadderlineWidth);
	

	///TODO: Draw The First Vertical Line (The Left Line) in the appropriate coordinates
	pWind->DrawLine(x12, y1, x12, y2);


	// ---- 2- Draw the Second Vertical Line ---- 
	int x34 = CellStartX + UI.CellWidth - UI.LadderXOffset; // same x (vertical line)
	                                                        // the y coordinates is the same as the First Vertical Line

	///TODO: Set pen color and width using the appropriate variables of UI_Info object (UI)

	pWind->SetPen(UI.LadderColor,UI.LadderlineWidth);

	///TODO: Draw The Second Vertical Line (The Right Line) in the appropriate coordinates
	pWind->DrawLine(x34, y1, x34, y2);

	// ---- 3- Draw the Cross Horizontal Lines ---- 
	int cincreas=toStartY;
	
	// The cross lines are drawn on the Horizontal Borders of the Cells between fromCell to toCell
	// Check the drawn ladders in the project document and imitate it

	///TODO: Draw the cross horizontal lines of the ladder using the appropriate coordinates

	while(cincreas<fromStartY)
	{
		cincreas+=UI.CellHeight;
	pWind->DrawLine(x12, cincreas, x34, cincreas);
	
	}
	
}

//////////////////////////////////////////////////////////////////////////////////////////

void Output::DrawSnake(const CellPosition & fromCell, const CellPosition & toCell) const
{
	cout<<"Snake v Cell value: " << fromCell.HCell() << " " << toCell.HCell()<< endl;
	cout<<"Snake v GetCellNum: " << fromCell.GetCellNum() << " " << toCell.GetCellNum()<< endl;
	///TODO: Validate the fromCell and toCell (Must be Vertical and toCell is below fromCell otherwise do NOT draw)
if ((fromCell.VCell()>=toCell.VCell())||(fromCell.HCell()!=toCell.HCell()))
	{
		cout<<"Snake "<< endl;
	return ;
	}


	// Get the upper left corner coordinates of the fromCell and toCell
	int CellStartX = GetCellStartX(fromCell); // same for fromCell and toCell (vertical)
	int fromStartY = GetCellStartY(fromCell);
	int toStartY = GetCellStartY(toCell);

	// ---- 1- Draw Line representing the Snake Body ----

	// Set coordinates of start and end points of the Line of the Snake's Body
	int x12 = CellStartX + UI.LadderXOffset/2; // same for the start and end point (vertical)
	int y1 = fromStartY + UI.CellHeight/2;
	int y2 = toStartY + UI.CellHeight/2;

	///TODO: Set pen color and width from the appropriate variables of the UI_Info object (UI)
	pWind->SetPen(UI.SnakeColor,UI.SnakelineWidth);
	


	///TODO: Draw the Line representing the Snake BOdy
	pWind->DrawLine(x12, y1, x12, y2);


	// ---- 2- Draw Polygon with Diamond Shape representing the Snake Head ----
	
	// Set Pen and Brush (background) of the Polygon
	pWind->SetPen(UI.SnakeColor, UI.SnakelineWidth);
	pWind->SetBrush(UI.SnakeColor);

	int yChange = UI.CellHeight / 4; // slight vertical difference to be used in the up and down polygon points
	int xChange = UI.CellWidth / 14; // slight horizontal difference to be used in the left and right polygon points

	///TODO: Set the coordinates of the 4 points of the Polygon
	//       Check the snakes drawn in the project document and draw it the same way
	
int x[4];
	x[0]=x12;
	x[1]=x12-xChange;
	x[2]=x12;
	x[3]=x12+xChange;
	int y[4];
	y[0]=y1;
	y[1]=y1+yChange;
	y[2]=y1+2*yChange;
	y[3]=y1+yChange;
	///TODO: Draw the Polygon (diamond) representing the Snake's Head
	//       Check the snakes drawn in the project document and draw it the same way
		pWind->DrawPolygon(x , y , 4, FILLED);



}

//////////////////////////////////////////////////////////////////////////////////////////

Output::~Output()
{
	// deallocating the window object
	delete pWind;
}