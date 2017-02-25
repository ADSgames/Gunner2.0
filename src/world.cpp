#include "world.h"

world::world(){


}

world::~world(){

}

void world::setup(){

  if (!(crate = load_bitmap("crate.png", NULL)))
    abort_on_error("Cannot find image crate.png\nPlease check your files and try again");

  if (!(cursor = load_bitmap("cursor.png", NULL)))
    abort_on_error("Cannot find image cursor.png\nPlease check your files and try again");

  if (!(helicopter_sprite = load_bitmap("helicopter.png", NULL)))
    abort_on_error("Cannot find image helicopter.png\nPlease check your files and try again");

  if (!(helicopter_hurt = load_bitmap("helicopter_hurt.png", NULL)))
    abort_on_error("Cannot find image helicopter_hurt.png\nPlease check your files and try again");

  if (!(character_sprite = load_bitmap("player.png", NULL)))
    abort_on_error("Cannot find image player.png\nPlease check your files and try again");

  if (!(character_hurt = load_bitmap("player_hurt.png", NULL)))
    abort_on_error("Cannot find image player_hurt.png\nPlease check your files and try again");

  if (!(background = load_bitmap("background.png", NULL)))
    abort_on_error("Cannot find image background.png\nPlease check your files and try again");

  create_enemy();
  game_character = new character();
  game_character -> setup( character_sprite, character_hurt, this);


}
//Helicopter factory
void world::create_enemy(){
  enemy *newEnemy = new enemy( helicopter_sprite, helicopter_hurt, this);
  game_enemies.push_back( newEnemy);
}

void world::delete_enemy(enemy* newEnemy){

  std::vector<enemy*>::iterator i;
  i=std::find(game_enemies.begin(),game_enemies.end(),newEnemy);

  if(i!=game_enemies.end()){
      game_enemies.erase(i);
  }
}

void world::delete_projectile(projectile* newProjectile){

  std::vector<projectile*>::iterator i;
  i=std::find(game_projectiles.begin(),game_projectiles.end(),newProjectile);

  if(i!=game_projectiles.end()){
      game_projectiles.erase(i);
  }
}

void world::create_item(int newType, int newX, int newY){

  if(newType==1)
    game_items.push_back(new item(crate,newX,newY,newType));
}

int world::get_character_x(){
  return game_character -> get_x();
}

int world::get_character_y(){
  return game_character -> get_y();
}

//Bullet factory
void world::create_projectile(int newX, int newY, bool newOwner, float newAngle, float newSpeed){
  game_projectiles.push_back(new projectile(newX,newY,newOwner,newAngle,newSpeed));
  projectile_delay = 0;
}

std::vector<projectile*>* world::get_projectiles(){

  return &game_projectiles;

}

void world::update(){

  game_character -> update();

  for( unsigned int i=0; i<game_enemies.size(); i++){
    game_enemies[i] -> update(0,0);
  }

  for( unsigned int i=0; i<game_projectiles.size(); i++){
    game_projectiles[i] -> update();
  }

  for( unsigned int i=0; i<game_items.size(); i++){
    game_items[i] -> update();
  }
  projectile_delay++;

}

void world::draw(BITMAP *tempBitmap){

  draw_sprite(tempBitmap,background,0,0);

  game_character -> draw(tempBitmap);




  for( unsigned int i = 0; i < game_projectiles.size(); i++){
    game_projectiles[i] -> draw(tempBitmap);
  }

  for( unsigned int i = 0; i < game_enemies.size(); i++){
    game_enemies[i] -> draw(tempBitmap);
  }

  for( unsigned int i = 0; i < game_items.size(); i++){
    game_items[i] -> draw(tempBitmap);
  }

  draw_sprite( tempBitmap, cursor, mouse_x - 10, mouse_y - 10);
}
