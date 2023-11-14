const int row1 = 31;
const int row2 = 36;
const int row3 = 41;
const int row4 = 34;
const int row5 = 48;
const int row6 = 42;
const int row7 = 47;
const int row8 = 44;
const int rows[8] = {row1,row2,row3,row4,row5,row6,row7,row8};

const int col1 = 35;
const int col2 = 46;
const int col3 = 45;
const int col4 = 32;
const int col5 = 43;
const int col6 = 33;
const int col7 = 37;
const int col8 = 38;
const int cols[8] = {col1,col2,col3,col4,col5,col6,col7,col8};

const int varXPin = A1;//X Value  from Joystick
const int varYPin = A2;//Y Value from Joystick

/*const int up = 3;
const int down = 4;
const int left = 5;
const int right = 2;*/

int tail[2];
int dir[30][2];
bool game_over = false;
int len = 1;

int board[8][8] = { {0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0}} ;

int gameover[8][8]={{0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0},
                    {1,1,1,0,0,1,1,1},
                    {0,0,0,0,0,0,0,0},
                    {0,0,1,1,1,1,0,0},
                    {0,1,0,0,0,0,1,0},
                    {1,0,0,0,0,0,0,1},
                    {0,0,0,0,0,0,0,0}} ;

int one[8][8] =   { {0,0,0,0,1,1,0,0},
                    {0,0,0,1,0,1,0,0},
                    {0,0,1,0,0,1,0,0},
                    {0,0,0,0,0,1,0,0},
                    {0,0,0,0,0,1,0,0},
                    {0,0,0,0,0,1,0,0},
                    {0,0,0,0,0,1,0,0},
                    {0,0,0,1,1,1,1,0}} ;

int two[8][8] = {   {0,0,0,1,1,1,0,0},
                    {0,0,1,0,0,0,1,0},
                    {0,0,1,0,0,0,1,0},
                    {0,0,0,0,0,1,0,0},
                    {0,0,0,0,1,0,0,0},
                    {0,0,0,1,0,0,0,0},
                    {0,0,1,0,0,0,0,0},
                    {0,0,1,1,1,1,1,0}} ;

int three[8][8] = { {0,0,0,1,1,1,0,0},
                    {0,0,1,0,0,0,1,0},
                    {0,0,0,0,0,0,1,0},
                    {0,0,0,0,0,1,0,0},
                    {0,0,0,0,1,0,0,0},
                    {0,0,0,0,0,1,0,0},
                    {0,0,1,0,0,0,1,0},
                    {0,0,0,1,1,1,0,0}} ;

int go[8][8] =    { {0,0,0,0,0,0,0,0},
                    {0,1,1,1,0,1,1,1},
                    {1,0,0,0,0,1,0,1},
                    {1,0,1,1,0,1,0,1},
                    {1,0,0,1,0,1,0,1},
                    {0,1,1,1,0,1,1,1},
                    {0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0}} ;

//int head[2];
bool t = true;
int newhead[2];
int apple[2];
int xaxis,yaxis;

void setup() {
  // put your setup code here, to run once:
  pinMode(varXPin, INPUT);
  pinMode(varYPin, INPUT);

  pinMode(up, INPUT);
  pinMode(down, INPUT);
  pinMode(left, INPUT);
  pinMode(right, INPUT);

  pinMode(row1, OUTPUT);
  pinMode(row2, OUTPUT);
  pinMode(row3, OUTPUT);
  pinMode(row4, OUTPUT);
  pinMode(row5, OUTPUT);
  pinMode(row6, OUTPUT);
  pinMode(row7, OUTPUT);
  pinMode(row8, OUTPUT);

  pinMode(col1, OUTPUT);
  pinMode(col2, OUTPUT);
  pinMode(col3, OUTPUT);
  pinMode(col4, OUTPUT);
  pinMode(col5, OUTPUT);
  pinMode(col6, OUTPUT);
  pinMode(col7, OUTPUT);
  pinMode(col8, OUTPUT);
  Serial.begin(9600);

  for(int i=0;i<8;i++){
    digitalWrite(rows[i],HIGH);
    digitalWrite(cols[i],LOW);
  }
 
  dir[0][0] = 1;
  dir[0][1] = 2;
  tail[0] = 1;
  tail[1] = 2;
  apple[0] = generate_dim();
  apple[1] = generate_dim();


}

void loop() {
  // put your main code here, to run repeatedly:
  if(t){
    t = false;
    start_game();
  }
  if(!game_over){ 
    check_apple();
    board[dir[0][0]][dir[0][1]] = 1;
    board[apple[0]][apple[1]] = 1;
    delay(1); 
    for(int i=0;i<8;i++){
      digitalWrite(rows[i],LOW);
      for(int j=0;j<8;j++){ 
        digitalWrite(cols[j],board[i][j]);
        //Serial.println(board[i][j]);
      }
      delay(2);
      digitalWrite(rows[i],HIGH);
    }
    delay(10);
  }
  else{
    for(int tem=0;tem<11;tem++){ 
      for(int i=0;i<8;i++){
        digitalWrite(rows[i],LOW);
        for(int j=0;j<8;j++){ 
          digitalWrite(cols[j],gameover[i][j]);
          //Serial.println(board[i][j]);
        }
        delay(2);
        digitalWrite(rows[i],HIGH);
      }
      delay(50);
    }
    delay(500);
    reset_board();
    t = true;
    game_over = false;
    len = 1;
    dir[0][0] = generate_dim();
    dir[0][1] = generate_dim();
    apple[0] = generate_dim();
    apple[1] = generate_dim();
    board[dir[0][0]][dir[0][1]] = 1;
    board[apple[0]][apple[1]] = 1;
    Serial.println("new game");
    delay(500);
    
  }
  
  xaxis = analogRead(varXPin);
  yaxis = analogRead(varYPin);
  while(right() || down() || up() || left()){ 
    //board[tail[0]][tail[1]] = 0;
    tail[0] = dir[len-1][0]; 
    tail[1] = dir[len-1][1];
    board[tail[0]][tail[1]] = 0;

  if(up()){
    newhead[0] = dir[0][0] - 1;
    newhead[1] = dir[0][1];
    if(newhead[0]==-1){
      newhead[0] = 7;
    }
    if(len>1) {check_game();}
    dir[0][0] = newhead[0];
    Serial.println("up");
    delay(100);
    break;
  }
  if(down()){
    newhead[0] = (dir[0][0] + 1)%8;
    newhead[1] = dir[0][1];
    if(len>1) {check_game();}
    dir[0][0] = newhead[0];
    Serial.println("down");
    delay(100);
    break;
  }
  if(left()){
    newhead[1] = dir[0][1] - 1;
    newhead[0] = dir[0][0];
    if(newhead[1]==-1){
      newhead[1] = 7;
    }
    if(len>1) {check_game();}
    dir[0][1] = newhead[1];
    Serial.println("left");
    delay(100);
    break;
  } 
  if(right()){
    newhead[1] = (dir[0][1] + 1)%8;
    newhead[0] = dir[0][0];
    if(len>1) {check_game();}
    dir[0][1] = newhead[1];
    Serial.println("right");
    delay(100);
    break;
  }  
  }
 
}

int generate_dim(){
  int x = (int)random(0,8);
  return x;
}

void light_row(int r, int cs[8]){
  digitalWrite(rows[r],LOW);
  for (int j=0; j<8;j++){
    digitalWrite(cols[j], cs[j]);
  }
  digitalWrite(rows[r],HIGH);

}

void check_apple(){
  if(dir[0][0] == apple[0] && dir[0][1] == apple[1]){
    // create new apple in the board
    Serial.println("in check_apple");
    apple[0] = generate_dim();
    apple[1] = generate_dim();
    board[apple[0]][apple[1]] = 1;
    // increase the len of the snake
    len ++;
    board[tail[0]][tail[1]] = 1;
    dir[len-1][0] = tail[0]; 
    dir[len-1][1] = tail[1];
    Serial.println(len);
  }
}

void check_game(){
        
  for(int i = len -1;i>0;i--){
    if (dir[i][0] == newhead[0] && dir[i][1] == newhead[1]){
      game_over = true;
      break;
    }
    dir[i][0] = dir[i-1][0];
    dir[i][1] = dir[i-1][1];
 }      
      
}

void reset_board(){
  for(int a=0;a<8;a++){
    for(int b=0;b<8;b++){
      board[a][b] = 0;
    }    
  }
}

bool right(){
  if((yaxis>900) && (xaxis>450) && (xaxis<536)){
    
    return true;
  }
  return false;
}
bool left(){
  if((yaxis<400) && (xaxis>450) && (xaxis<536)){
    
    return true;
  }
  return false;
}
bool up(){
    if((xaxis>900) && (yaxis>450) && (yaxis<536)){
   
    return true;
  }
  return false;
}
bool down(){
  if((xaxis<400) && (yaxis>450) && (yaxis<536)){
    
    return true;
  }
  return false;
}

void start_game(){
  // number 3
  for(int tem=0;tem<50;tem++){ 
  for(int i=0;i<8;i++){
    digitalWrite(rows[i],LOW);
    for(int j=0;j<8;j++){ 
      digitalWrite(cols[j],three[i][j]);
      //Serial.println(board[i][j]);
    }
    delay(2);
    digitalWrite(rows[i],HIGH);
  }
  }

  // number 2
  for(int tem=0;tem<50;tem++){ 
  for(int i=0;i<8;i++){
    digitalWrite(rows[i],LOW);
    for(int j=0;j<8;j++){ 
      digitalWrite(cols[j],two[i][j]);
      //Serial.println(board[i][j]);
    }
    delay(2);
    digitalWrite(rows[i],HIGH);
  }
  }

  // number one
  for(int tem=0;tem<50;tem++){ 
  for(int i=0;i<8;i++){
    digitalWrite(rows[i],LOW);
    for(int j=0;j<8;j++){ 
      digitalWrite(cols[j],one[i][j]);
      //Serial.println(board[i][j]);
    }
    delay(2);
    digitalWrite(rows[i],HIGH);
  }
  }

  // go!!!
  for(int tem=0;tem<50;tem++){ 
  for(int i=0;i<8;i++){
    digitalWrite(rows[i],LOW);
    for(int j=0;j<8;j++){ 
      digitalWrite(cols[j],go[i][j]);
      //Serial.println(board[i][j]);
    }
    delay(2);
    digitalWrite(rows[i],HIGH);
  }
  }
}
