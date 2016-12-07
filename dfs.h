#include <stack>

using namespace std;

const char _blank_chess = '.';
const char _blue_chess = 'B';
const char _red_chess = 'R';
const int _size = 11;

template <typename _Ty>
class Board
{
public:
   Board(): _board() {
       for (int i = 0; i < _size; ++i)
       {
           for (int j = 0; j < _size; ++j)
           {
               _board[i][j] = 0;
           }
       }
   }
   // 从外部导入棋盘矩阵
   Board(_Ty __board[11][11]) {
       for (int i = 0; i < _size; ++i)
       {
           for (int j = 0; j < _size; ++j)
           {
               _board[i][j] = __board[i][j];
           }
       }
   }

   ~Board() {}

   bool legal(int x, int y) {
       return !(x < 0 || x > 10 || y < 0 || y > 10);
   }

   _Ty &at(int x, int y) {
       return _board[x][y];
   }
private:
   _Ty _board[_size][_size];
};

struct Move
{
public:
   Move(int x, int y): x(x), y(y) {}
   ~Move() {}

   int x;
   int y;
};

class redDFS
{
public:
   redDFS(Board<char> *_board, char type): _board(_board), type(type) {

   }
   ~redDFS() {}

   bool solve() {
       // 寻找x = 0的点
       for (int j = 0; j < _size; ++j)
       {
           if (_board->at(0, j) == type)
           {
               moves.push(Move(0, j));
           }
       }
       return dfs_find();
   }
private:
   inline void add_neighbor(int x, int y) {
       if (_board->legal(x, y) && _board->at(x, y) == type && !history.at(x, y))
       {
           moves.push(Move(x, y));
           history.at(x, y) = true;
       }
   }
   // 自上向下搜索
   bool dfs_find() {
       if (moves.size() == 0) { return  false; }
       Move &current_move = moves.top();
       // 当找到x = 10的点
       if (current_move.x == _size - 1) { return true; }
       int x = current_move.x,
           y = current_move.y;
       moves.pop();
       add_neighbor(x - 1, y);
       add_neighbor(x - 1, y + 1);
       add_neighbor(x, y - 1);
       add_neighbor(x, y + 1);
       add_neighbor(x + 1, y - 1);
       add_neighbor(x + 1, y);
       return dfs_find();
   }

   stack<Move> moves;
   char type;
   Board<bool> history;
   Board<char> *_board;
};

class blueDFS
{
public:
   blueDFS(Board<char> *_board, char type): _board(_board), type(type) {

   }
   ~blueDFS() {}

   bool solve() {
       // 寻找x = 0的点
       for (int j = 0; j < _size; ++j)
       {
           if (_board->at(j, 0) == type)
           {
               moves.push(Move(j, 0));
           }
       }
       return dfs_find();
   }
private:
   inline void add_neighbor(int x, int y) {
       if (_board->legal(x, y) && _board->at(x, y) == type && !history.at(x, y))
       {
           moves.push(Move(x, y));
           history.at(x, y) = true;
       }
   }
   // 自上向下搜索
   bool dfs_find() {
       if (moves.size() == 0) { return  false; }
       Move &current_move = moves.top();
       // 当找到x = 10的点
       if (current_move.y == _size - 1) { return true; }
       int x = current_move.x,
           y = current_move.y;
       moves.pop();
       add_neighbor(x - 1, y);
       add_neighbor(x - 1, y + 1);
       add_neighbor(x, y - 1);
       add_neighbor(x, y + 1);
       add_neighbor(x + 1, y - 1);
       add_neighbor(x + 1, y);
       return dfs_find();
   }

   stack<Move> moves;
   char type;
   Board<bool> history;
   Board<char> *_board;
};
