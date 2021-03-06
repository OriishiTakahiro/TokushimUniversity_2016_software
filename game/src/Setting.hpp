#ifndef SETTING_H
#define SETTING_H

#define FRAME_TERM 40
#define PHYSICS_CALC_TERM 16
#define ROOMBA_SPEED 1500.0			// [px/sec]
#define DEFAULT_LIFE 20
#define ROOMBA_RADIUS 50

#define FONT_PATH "../assets/SNsanafonObiV250.ttf"

#define GAME_TITLE "死守！ルンバ暴走！"

// ------ for field ------ //
#define GAME_FIELD_WIDTH 3000
#define GAME_FIELD_HEIGHT 800
// ------ for field ------ //

// ------ for window ------ //
#define GAME_WINDOW_WIDTH 1500
#define GAME_WINDOW_HEIGHT 800
// ------ for window ------ //

// ------ for network ------ //
#define NETWORK_INTERFACE "eth0"
#define CLIENT_DEST_PORT 8080
#define CLIENT_RECV_PORT 6060
#define SERVER_DEST_PORT 6060
#define SERVER_RECV_PORT 8080
// ------ for network ------ //

// ------ for wii remote ------ //
#define POINT_X_MIN 0
#define POINT_X_MAX 1791
#define POINT_Y_MIN 0
#define POINT_Y_MAX 1272
// ------ for wii remote ------ //


// ------ start window ------ //
#define TIME_SEC_SHOW_TITLE 5
#define TITLE_IMG_PATH "../assets/title.png" 
#define SCINARIO_IMG_PATH "../assets/scinario.png" 
// ------ start window ------ //

// ------ game window ------ //
#define GAME_WINDOW_BACKGROUND_PATH "../assets/ground.png"
#define RUNAWAY_ROOMBA_IMG_PATH "../assets/roomba3.png"
#define EXPLODED_ROOMBA_IMG_PATH "../assets/exploded_roomba.png"
#define CUSTOMIZED_ROOMBA_IMG_PATH "../assets/roomba2.png"
#define EQUIPMENT_RIGHT_SIDE_IMG_PATH "../assets/equipment1.png"
#define EXPLODED_EQUIP_RIGHT_SIDE_IMG_PATH "../assets/exploded_equipment1.png"
#define EQUIPMENT_LEFT_SIDE_IMG_PATH "../assets/equipment2.png"
#define EXPLODED_EQUIP_LEFT_SIDE_IMG_PATH "../assets/exploded_equipment2.png"
#define LIFE_PANEL_IMG_PATH "../assets/lifepanel.png"
#define GAME_WIN_IMG_PATH "../assets/win2.png"
#define GAME_LOSE_IMG_PATH "../assets/lose2.png"

#define EQUIPMENT_WIDTH 259
#define EQUIPMENT_HEIGHT 400
#define LIFE_PANEL_WIDTH 200
#define LIFE_PANEL_HEIGHT 141
// ------ game window ------ //


#endif
