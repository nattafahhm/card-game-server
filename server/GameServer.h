#ifndef __StarServer__GameServer__#define __StarServer__GameServer__#include "StarSocketServer.h"#define HEADER		s16#define CODE		s16#define ONLINE                                  1#define OFFLINE                                 0#define TRUE                                    1#define FALSE                                   0#define UUID_LENGTH                             128#define ROOM_NAME_LENGTH                        32#define ROOM_PASS_LENGTH                        16#define USER_NAME_LENGTH                        32#define MIN_NAME_LENGTH                         1#define TOKEN_LENGTH                            32#define FREE_USER_SLOT                          0//PLAYING#define NO_GAME                                  0#define NO_ROOM                                  -1#define NO_SEAT                                  -1#define NO_CARD                                  0#define PLAYER_ACTION_NONE                      -10#define PLAYER_ACTION_FOLD                       -1#define PLAYER_ACTION_VALUE_0                    0#define PLAYER_ACTION_VALUE_1                    1#define PLAYER_ACTION_VALUE_2                    2#define PLAYER_ACTION_VALUE_3                    3#define PLAYER_ACTION_VALUE_4                    4//CONFIG SERVER AND GAME#define MAX_TEMP_RANDOM                         64#define MAX_CARD                                80 //60#define MAX_SUIT                                16//12#define MAX_CLUB                                5        #define MAX_ROOM                                64#define MAX_SEAT                                4#define MAX_PLAYER                              2 * MAX_ROOM*MAX_SEAT#define MIN_COIN                                0#define CHIP_STEP_DEFAULT                       0#define CHIP_STEP_LENGTH                        6// GAME STATE// PLAYER GAME ACTION HEADER#define PLAYER_GAME_ACTION_HEADER               5000#define PLAYER_GAME_ACTION_CODE_FOLD            6000#define PLAYER_GAME_ACTION_CODE_VALUE_0         100#define PLAYER_GAME_ACTION_CODE_VALUE_1         101#define PLAYER_GAME_ACTION_CODE_VALUE_2         102#define PLAYER_GAME_ACTION_CODE_VALUE_3         103#define PLAYER_GAME_ACTION_CODE_VALUE_4         104// -- ERROR#define PLAYER_GAME_ACTION_CODE_ERROR           404     // ERROR UNKNOWN CASE#define GAME_STATE_WAIT                         0       // WAIT 2 PLAYER JOIN#define GAME_STATE_LOADING                      1#define GAME_STATE_INIT_MATCH                   2       // INIT GAME SETTING#define GAME_STATE_FOLD_CARD                    3       // BEGIN MATCH#define GAME_STATE_IN_MATCH                     4       // PLAYING#define GAME_STATE_CALCULATE_MATCH_RESULT       5       // CALCULATE RESULT#define GAME_STATE_POST_MATCH                   6       // SHOW RESULT#define GAME_STATE_SHOW                         7#define GAME_STATE_END_GAME                     8       // END GAME#define GAME_STATE_ERROR                        -1      // ERROR//LOGIN HEADER#define LOGIN_HEADER                            1000//OK#define LOGIN_CODE_OK                           100#define LOGIN_CODE_REJOIN_OK                    101#define LOGIN_CODE_REJOIN_END                   102#define LOGIN_CODE_NEW_USER                     103//FAIL#define LOGIN_CODE_BANNED                       300#define LOGIN_CODE_ALREADY_LOGIN                301//ERROR#define LOGIN_CODE_ERROR                        404// REGISTER HEADER#define REGISTER_HEADER                         1001// -- OK#define REGISTER_CODE_OK                        100     // REGISTER OK// -- FAIL#define REGISTER_CODE_NAME_DUPLICATE            300     // NAME ALREADY EXISTS#define REGISTER_CODE_NAME_SHORT                301     // NAME LENGTH TOO SHORT#define REGISTER_CODE_NAME_BAD                  302     // BAD WORD OR SPECIAL// -- ERROR#define REGISTER_CODE_ERROR                     404     // ERROR UNKNOWN CASE#define JOIN_ROOM_CODE_OK                       100     // JOIN OK// QUICK JOIN ROOM HEADER#define QUICK_JOIN_ROOM_HEADER                  2002// -- OK#define QUICK_JOIN_ROOM_CODE_OK                 100     // QUICK JOIN OK// -- FAIL#define QUICK_JOIN_ROOM_CODE_NOT_ENOUGH_GOLD    300     // NOT ENOUGH GOLD#define QUICK_JOIN_ROOM_CODE_FULL               301     // NO EMPTY ROOM FOR CREATE// -- ERROR#define QUICK_JOIN_ROOM_CODE_ERROR              404     // ERROR UNKNOWN CASE// LEAVE ROOM HEADER#define LEAVE_ROOM_HEADER                       2003#define LEAVE_ROOM_CODE_OK                      100     // LEAVE OK#define LEAVE_ROOM_CODE_ERROR                   404     // ERROR UNKNOWN CASE// GAME PULLING HEADER#define GAME_PULLING_HEADER                     5001#define GAME_PULLING_CODE_UPDATE                100     // HAVE CHANGE#define GAME_PULLING_CODE_LATEST                101     // LATEST DATA#define GAME_PULLING_CODE_ERROR                 404     // ERROR UNKNOWN CASE// FETCH DATA HEADER#define FETCH_DATA_HEADER                       6000// -- OK#define FETCH_DATA_CODE_USERDATA                100     // FETCH USERDATA OK// -- ERROR#define FETCH_DATA_CODE_ERROR                   404#define LOBBY_ACTION_HEADER                     7000#define LOBBY_ACTION_CODE_TOTAL_USERS           100#define LOBBY_ACTION_CODE_RANKING               200#define LOBBY_ACTION_CODE_ERROR                 404#define SHOP_ACTION_HEADER                     8000#define SHOP_ACTION_CODE                       100#define SHOP_ACTION_CODE_CHARACTER             200#define SHOP_ACTION_CODE_ERROR                 404#define TIME_LOGDING                            5000    // ms #define TIME_INIT_MATCH                         10000   // ms#define TIME_FOLD_CARD                          3000    // ms#define TIME_CALCULATE                          1000    // ms#define TIME_IN_GAME                            10000   // ms#define TIME_POST_MATCH                         10000   // ms#define TIME_FORCE_RESET_ROOM                   2500    // ms#define STATUS_DEFAULT                          0#define STATUS_TRUE                             100#define STATUS_FALSE                            1#define LEVELUP                                 1000#define WORLD_LAYOUT                            2typedef struct{    u32         userId;    char        uuid[UUID_LENGTH];    char        email[UUID_LENGTH];    char        name[USER_NAME_LENGTH];    s8          characterId;    u32         rankId;    u32         gold;      u32         exp;    u32         level;    u32         winCount;    u32         loseCount;    u32         timeRemainGold;    u32         coins;    u32         bestScore;}UserData;typedef struct{    UserData    user;    s16         roomId;    s16         seatId;}ServerUserData;typedef struct {    s8 id;    s8 club;}Cards;typedef struct{    UserData    user;    s8          online;    Cards       card[MAX_CARD];    s8          action;    u32         exp;    u32         level;    u32         winCount;    u32         loseCount;    s16         cardIndexPlayer;    u32         remainCardsPlayer;    u32         coins;    s8          winnerSeatId;}PlayerData;typedef struct{    s16         roomId;    s16         seatId;    u32         gameId;    char        name[ROOM_NAME_LENGTH];    s8          minChip;    s8          gameState;    s8          currentPlayer;    s16         remainCards;    Cards       lastCardIndex;    u32         lastestUpdateId;    PlayerData  players[MAX_SEAT];    char        button[MAX_CLUB];    char        listenner[MAX_CLUB];    u32         coinsRoom;    s8          statusCard[MAX_CLUB];    s8          layout;}GameRoomData;typedef struct{    const s16   roomId;    u32         gameId;    u32         token;    char        name[ROOM_NAME_LENGTH];    char        pass[ROOM_PASS_LENGTH];    s8          minChip;    s8          gameState;    s8          currentPlayer;    u32         lastestUpdateId;    s8          playerCount;    u32         time;    Cards       cards[MAX_CARD];    s16         nextCardIndex;    Cards       lastCardIndex;    PlayerData  players[MAX_SEAT];    s8          randIndex;    u32         tempRand[MAX_TEMP_RANDOM];    char        button[MAX_CLUB];    u32         coinsRoom;    s8          roundDrawCard;    char        listenner[MAX_CLUB];    s8          btn_count[MAX_CLUB];    s8          statusCard[MAX_CLUB];    s8          layout;    u32         tmpGold;    u32         tmpExp;    u32         tmpLevel;    u32         tmpWinCount;    u32         tmpLoseCount;    u32         bestScore;    pthread_mutex_t pull_mutex;    pthread_mutex_t room_mutex;}ServerRoomData;typedef struct{    HEADER      header;    CODE        code;    char        uuid[UUID_LENGTH];    char        email[UUID_LENGTH];    char        name[USER_NAME_LENGTH];    s8          characterId;}RegisterRequest;typedef struct{    HEADER       header;    CODE         code;}RegisterResponse;typedef struct {    HEADER      header;    CODE        code;    char        uuid[UUID_LENGTH];    char        email[UUID_LENGTH];}LoginRequest;typedef struct{    HEADER      header;    CODE        code;    u32         latestGameId;    s16         latestRoomId;    s16         latestSeatId;    UserData    user;}LoginResponse;typedef struct {    HEADER      header;    CODE        ignore16; }QuickJoinRoomRequest;typedef struct {    HEADER      header;    CODE        code;        GameRoomData gameRoom;}QuickJoinRoomResponse;typedef struct {    HEADER header;    CODE   code;}LeaveRoomRequest;typedef struct {    }LeaveRoomResponse;typedef struct {    HEADER      header;    CODE        code;}PlayerGameActionRequest;typedef struct {    HEADER      header;    CODE        code;}PlayerGameActionResponse;typedef struct {    HEADER      header;    CODE        ignore16;    u32         lastestUpdateId;}GamePullingGameRequest;typedef struct {    HEADER      header;    CODE        code;}GamePullingLatestGameResponse;typedef struct {    HEADER      header;    CODE        code;    GameRoomData gameRoom;}GamePullingUpdateGameResponse;typedef struct {    HEADER      header;    CODE        code;}FetchDataRequest;typedef struct {    HEADER      header;    CODE        code;    UserData    user;}FetchUserDataResponse;typedef struct {    HEADER      header;    CODE        code;    s8          id;}LobbyActionRequest;typedef struct {    HEADER          header;    CODE            code;    char            uuid[UUID_LENGTH];    char            email[UUID_LENGTH];    u32             rankId;    char            name[USER_NAME_LENGTH];    s8              characterId;    u32             level;    u32             bestScore;    u32             total_users;}LobbyActionRankingResponse;typedef struct {    HEADER      header;    CODE        code;    s8          character_id;}ShopActionRequest;typedef struct {    HEADER          header;    CODE            code;    s8              character_id;    s8              level_status;    s8              gold_status;    s8              character_status;}ShopActionResponse;void InitGameServer     ();void ClientConnect      (Client_t* client);void ClientRequest      (Client_t* client);void ClientDisconnect   (Client_t* client);void DestroyGameServer  ();void ProcessRequest     (Client_t* client, char* buffer, u32 buffer_size);#endif /* defined(__StarServer__GameServer__) */