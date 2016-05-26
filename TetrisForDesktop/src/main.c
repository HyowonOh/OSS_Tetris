#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include "Constant.h"
#include "TetrisView.h"
#include "TetrisManager.h"

int main(int argc, char* argv[]){
	TetrisView tetrisView;
	int processType;
	int direction;
	DWORD tickCount;
	int isSetMainMenu = False;
	do{
		TetrisView_ProcessMainMenu(&tetrisView);
		switch (tetrisView.mainMenu){
		case START_MAIN_MENU:
			TetrisView_StartGame(&tetrisView); //���� ���� ȭ��
			tickCount = GetTickCount();
			while (True){
				processType = AUTO; 
				direction = DOWN; // processType�� direction�� �����Ͽ� �ڵ����� �Ʒ��������� ����� ���������� ��
				isSetMainMenu = False; //���� �÷��� ȭ������ �̵�
				while (True){
					if (GetTickCount() - tickCount > TetrisView_GetDownMilliSecond(&tetrisView)){ //�� �������� ������ ����� ������ ������ �ɰ��� ������� ����
						processType = AUTO;
						direction = DOWN;
						tickCount = GetTickCount();
						break;
					}
					if (_kbhit()){
						int key = _getch();
						if (key == 0xE0 && _kbhit()){ // Ű���� 224�̰ų� �񵿱������� üũ�Ͽ� �Է� ���� ���� ������ �Էµ��� Ȯ��
							key = _getch();
							if (key == UP_KEY_CODE){ //Constant.h�� ����Ǿ� �ִ� ���� �Է¹���
								processType = DIRECTION; //�׿� �°� ����� Ÿ���� ����
								direction = UP;
								break;
							}
							if (key == DOWN_KEY_CODE){
								processType = DIRECTION;
								direction = DOWN;
								tickCount = GetTickCount();
								break;
							}
							if (key == LEFT_KEY_CODE){
								processType = DIRECTION;
								direction = LEFT;
								break;
							}
							if (key == RIGHT_KEY_CODE){
								processType = DIRECTION;
								direction = RIGHT;
								break;
							}
						}
						else{
							if (key == SPACE_BAR_KEY_CODE){ //�����̽��ٸ� �Է����� ���
								processType = DIRECT_DOWN; //���� �Ʒ��������� �������� ���
								tickCount = GetTickCount();
								break;
							}
							if (key == ESC_KEY_CODE){ //ESCŰ�� �Է����� ���
								TetrisView_PauseGame(&tetrisView); //����ȭ�� ���
								if (tetrisView.pauseMenu == MAIN_MENU_PAUSE_MENU){ //Main Menu�� ���ư��� ���ý�
									isSetMainMenu = True; 
									break;
								}
								processType = AUTO; //�ڵ����� ����
								tickCount = GetTickCount();
								break;
							}
							if (key == L_KEY_CODE){ //���� ����� Ȧ�� �Ҽ� �ִ� Ű
								TetrisView_MakeHold(&tetrisView);
							}
						}
						if (key == ITEM_FIRST_CODE){  //ù��° ������ ��� Z
							TetrisManager_UseItem(&tetrisView.tetrisManager, 1);
							break;
						}
						if (key == ITEM_SECOND_CODE){ //�ι�° ������ ��� X
							TetrisManager_UseItem(&tetrisView.tetrisManager, 2);
							break;
						}
						if (key == ITEM_THRID_CODE){  //����° ������ ��� X
							TetrisManager_UseItem(&tetrisView.tetrisManager, 3);
							break;
						}
						if (key == ITEM_FOURTH_CODE){ //�׹�° ������ ��� V
							TetrisManager_UseItem(&tetrisView.tetrisManager, 4);
							break;
						}
					}
				}

				//for selecting main menu at pause menu
				if (isSetMainMenu){
					break;
				}//������ �ߴ� �Ǿ��� ��� 
				TetrisView_ProcessGame(&tetrisView, processType, direction);
				if (tetrisView.endMenu == RANKING_END_MENU){ 
					TetrisView_AddRanking(&tetrisView); //Rank ���
					TetrisView_ShowRanking(&tetrisView); //��ü Ranking ��ȸ
					break;
				}
				else if (tetrisView.endMenu == MAIN_MENU_END_MENU){ //������ ��ü ���� �Ǿ����鼭 Main Menu�� �̵��ϰ� ��
					break;
				}
				else if (tetrisView.endMenu == EXIT_END_MENU){ //���α׷� ����
					tetrisView.mainMenu = EXIT_MAIN_MENU;
					break;
				}
			}
			break;
		case RANKING_MAIN_MENU: // Main Menu���� Ranking ȭ������ �̵�
			TetrisView_ShowRanking(&tetrisView);
			break;
		case SETTING_MAIN_MENU: // Main Menu Settingȭ������ �̵�
			TetrisView_ShowSetting(&tetrisView);
			break;
		}
	} while (tetrisView.mainMenu != EXIT_MAIN_MENU); // Main Menu���� ���α׷� ����
	return 0;
}