#include <stdio.h>
#include <stdlib.h>
#include "SDL2/SDL.h"

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The surface contained by the window
SDL_Surface* gScreenSurface = NULL;
SDL_Renderer* gRenderer = NULL;

const int SCREEN_WIDTH = 256,
          SCREEN_HEIGHT = 240;

//Starts up SDL and creates window
bool init();
//Frees media and shuts down SDL
void close();

void drawTile();

typedef unsigned short color[3];
const color gNesColorPalette[0x40] = {{0x7C,0x7C,0x7C}, //0x00
                                      {0x00,0x00,0xFC},
                                      {0x00,0x00,0xBC},
                                      {0x44,0x28,0xBC},
                                      {0x94,0x00,0x84},
                                      {0xA8,0x00,0x20},
                                      {0xA8,0x10,0x00},
                                      {0x88,0x14,0x00},
                                      {0x50,0x30,0x00},
                                      {0x00,0x78,0x00},
                                      {0x00,0x68,0x00},
                                      {0x00,0x58,0x00},
                                      {0x00,0x40,0x58},
                                      {0x00,0x00,0x00},
                                      {0x00,0x00,0x00},
                                      {0x00,0x00,0x00},
                                      {0xBC,0xBC,0xBC}, //0x10
                                      {0x00,0x78,0xF8},
                                      {0x00,0x58,0xF8},
                                      {0x68,0x44,0xFC},
                                      {0xD8,0x00,0xCC},
                                      {0xE4,0x00,0x58},
                                      {0xF8,0x38,0x00},
                                      {0xE4,0x5C,0x10},
                                      {0xAC,0x7C,0x00},
                                      {0x00,0xB8,0x00},
                                      {0x00,0xA8,0x00},
                                      {0x00,0xA8,0x44},
                                      {0x00,0x88,0x88},
                                      {0x00,0x00,0x00},
                                      {0x00,0x00,0x00},
                                      {0x00,0x00,0x00},
                                      {0xF8,0xF8,0xF8}, //0x20
                                      {0x3C,0xBC,0xFC},
                                      {0x68,0x88,0xFC},
                                      {0x98,0x78,0xF8},
                                      {0xF8,0x78,0xF8},
                                      {0xF8,0x58,0x98},
                                      {0xF8,0x78,0x58},
                                      {0xFC,0xA0,0x44},
                                      {0xF8,0xB8,0x00},
                                      {0xB8,0xF8,0x18},
                                      {0x58,0xD8,0x54},
                                      {0x58,0xF8,0x98},
                                      {0x00,0xE8,0xD8},
                                      {0x78,0x78,0x78},
                                      {0x00,0x00,0x00},
                                      {0x00,0x00,0x00},
                                      {0xFC,0xFC,0xFC}, //0x30
                                      {0xA4,0xE4,0xFC},
                                      {0xB8,0xB8,0xF8},
                                      {0xD8,0xB8,0xF8},
                                      {0xF8,0xB8,0xF8},
                                      {0xF8,0xA4,0xC0},
                                      {0xF0,0xD0,0xB0},
                                      {0xFC,0xE0,0xA8},
                                      {0xF8,0xD8,0x78},
                                      {0xD8,0xF8,0x78},
                                      {0xB8,0xF8,0xB8},
                                      {0xB8,0xF8,0xD8},
                                      {0x00,0xFC,0xFC},
                                      {0xF8,0xD8,0xF8},
                                      {0x00,0x00,0x00},
                                      {0x00,0x00,0x00}
                                      };

bool init()
{
  //Initialization flag
  int success = true;

  //Initialize SDL
  if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
  {
    printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
    success = false;
  }
  else
  {
    //Create window
    gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
    if( gWindow == NULL )
    {
      printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
      success = false;
    }
    else
    {
      //Get window renderer
      gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
      SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
    }
  }

  return success;
}

void close()
{

  //Destroy window
  SDL_DestroyWindow( gWindow );
  gWindow = NULL;
  SDL_DestroyRenderer(gRenderer);
  gRenderer = NULL;
  //Quit SDL subsystems
  SDL_Quit();
}

int main( int argc, char* args[] )
{
  //Start up SDL and create window
  if( !init() )
  {
    printf( "Failed to initialize!\n" );
    //Free resources and close SDL
    close();
    return 0;
  }

  //Main loop flag
  int quit = false;

  //Event handler
  SDL_Event e;

//0000000000007E3C 3C7E7EFFFFFF4200

  //While application is running
  while( !quit )
  {
    //Handle events on queue
    while( SDL_PollEvent( &e ) != 0 )
    {
      //User requests quit
      if( e.type == SDL_QUIT)
      {
        quit = true;
      }
    }
    SDL_SetRenderDrawColor(gRenderer, 0xFF,0xFF,0xFF,0xFF);
    SDL_RenderClear(gRenderer);
    drawTile();
    SDL_RenderPresent(gRenderer);
    SDL_Delay(500);
    //Update the surface
    // SDL_UpdateWindowSurface( gWindow );
  }
  close();
}

void drawTile() {

  unsigned short Mushroom[16] = {
    0x00,0x00,0x00,0x00,0x00,0x00,0x7E,0x3C,
    0x3C,0x7E,0x7E,0xFF,0xFF,0xFF,0x42,0x00
  };
  unsigned short palette[4] = {
                              0x11,
                              0x37,
                              0x17,
                              0x0F
                          };
  const unsigned int x_origin = 20;
  const unsigned int y_origin = 20;
  for (int line = 0 ; line < 8 ; line++) {
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION,
                    SDL_LOG_PRIORITY_INFO,
                    "Drawing Line %d (y = %d) \n",line, y_origin + line);

    for (int bitMask = 1; bitMask <= 0x80 ; bitMask <<= 1) {

      unsigned int colorIndex = 0;
      unsigned int x_offset = 0;
      unsigned int bitIndex = 0;
      unsigned int bitCounter = bitMask;

      while(bitCounter != 0) {
        bitCounter >>= 1;
        x_offset +=1;
      }
      if((Mushroom[line] & bitMask) && (Mushroom[line+8] & bitMask)) {
        colorIndex = 3;
      }
      if((Mushroom[line] & bitMask) && !(Mushroom[line+8] & bitMask)) {
        colorIndex = 1;
      }
      if(!(Mushroom[line] & bitMask) && (Mushroom[line+8] & bitMask)) {
        colorIndex = 2;
      }

      SDL_SetRenderDrawColor( gRenderer,  gNesColorPalette[palette[colorIndex]][0],
                                          gNesColorPalette[palette[colorIndex]][1],
                                          gNesColorPalette[palette[colorIndex]][2],
                                          gNesColorPalette[palette[colorIndex]][3]);
      SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION,
                     SDL_LOG_PRIORITY_INFO,
                     "Drawn Pixel at x_offset= %d, color: %d \n",
                     x_offset,
                     colorIndex);
      SDL_RenderDrawPoint(gRenderer, x_origin+x_offset, y_origin+line);
    }
  }
}
