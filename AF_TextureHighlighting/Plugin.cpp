// This file added in headers queue
// File: "Sources.h"
#include "resource.h"

namespace GOTHIC_ENGINE {

  // TO DO
  // Your code ...


  void Game_Entry() {
  }
  
  void Game_Init() {
    Plugin_InitConsole();
  }

  void Game_Exit() {
  }

  void Game_PreLoop() {
  }
  const int v = v;

  void Game_Loop() {
    if (texture_view)
    {
    zCVob* cameraVob = ogame->GetCameraVob();
    oCWorld* gameWorld = ogame->GetGameWorld();

    zCPolygon* poly = nullptr;

    zVEC3 cameraPos = cameraVob->GetPositionWorld();
    zVEC3 rayAt = cameraVob->GetAtVectorWorld() * 1000.0f;

    int crosshair_width = screen->psizex / 100;
    zlineCache->Line(
      screen->psizex / 2 - crosshair_width, 
      screen->psizey / 2 - crosshair_width,
      screen->psizex / 2 + crosshair_width,
      screen->psizey / 2 + crosshair_width,
      GFX_CYAN);
    zlineCache->Line(
      screen->psizex / 2 + crosshair_width, 
      screen->psizey / 2 - crosshair_width,
      screen->psizex / 2 - crosshair_width,
      screen->psizey / 2 + crosshair_width,
      GFX_CYAN);


    if (gameWorld->TraceRayNearestHit(cameraPos, rayAt, (zCVob*)0, zTRACERAY_STAT_POLY))
    {
      zCPolygon* poly = gameWorld->traceRayReport.foundPoly;
      if (!poly) return;

      for (size_t i = 0; i < poly->polyNumVert; i++)
      {
        if (i == poly->polyNumVert - 1)
        {
          zlineCache->Line3D(poly->vertex[i]->position, poly->vertex[0]->position, GFX_CARROT, FALSE);
          break;
        }
        zlineCache->Line3D(poly->vertex[i]->position, poly->vertex[i + 1]->position, GFX_CARROT, FALSE);
      }

      zlineCache->Line3D(cameraPos, poly->GetCenter(), GFX_GREEN, FALSE);
      zSTRING text = poly->material->texture->GetObjectName();
      int font_height = screen->FontY() * 1.5;
      screen->Print(4096 - screen->FontSize(text)/2, 300 + font_height * 1, poly->material->texture->GetObjectName());
      screen->Print(4096 - screen->FontSize(text)/2, 300 + font_height * 2, poly->material->GetName());
      screen->Print(4096 - screen->FontSize(text)/2, 300 + font_height * 3, "Alpha blend: " + poly->material->GetAlphaBlend());
    }

    }

  }

  void Game_PostLoop() {
  }

  void Game_MenuLoop() {
  }

  // Information about current saving or loading world
  TSaveLoadGameInfo& SaveLoadGameInfo = UnionCore::SaveLoadGameInfo;

  void Game_SaveBegin() {
  }

  void Game_SaveEnd() {
  }

  void LoadBegin() {
  }

  void LoadEnd() {
  }

  void Game_LoadBegin_NewGame() {
    LoadBegin();
  }

  void Game_LoadEnd_NewGame() {
    LoadEnd();
  }

  void Game_LoadBegin_SaveGame() {
    LoadBegin();
  }

  void Game_LoadEnd_SaveGame() {
    LoadEnd();
  }

  void Game_LoadBegin_ChangeLevel() {
    LoadBegin();
  }

  void Game_LoadEnd_ChangeLevel() {
    LoadEnd();
  }

  void Game_LoadBegin_Trigger() {
  }
  
  void Game_LoadEnd_Trigger() {
  }
  
  void Game_Pause() {
  }
  
  void Game_Unpause() {
  }
  
  void Game_DefineExternals() {
  }

  void Game_ApplyOptions() {
  }

  /*
  Functions call order on Game initialization:
    - Game_Entry           * Gothic entry point
    - Game_DefineExternals * Define external script functions
    - Game_Init            * After DAT files init
  
  Functions call order on Change level:
    - Game_LoadBegin_Trigger     * Entry in trigger
    - Game_LoadEnd_Trigger       *
    - Game_Loop                  * Frame call window
    - Game_LoadBegin_ChangeLevel * Load begin
    - Game_SaveBegin             * Save previous level information
    - Game_SaveEnd               *
    - Game_LoadEnd_ChangeLevel   *
  
  Functions call order on Save game:
    - Game_Pause     * Open menu
    - Game_Unpause   * Click on save
    - Game_Loop      * Frame call window
    - Game_SaveBegin * Save begin
    - Game_SaveEnd   *
  
  Functions call order on Load game:
    - Game_Pause              * Open menu
    - Game_Unpause            * Click on load
    - Game_LoadBegin_SaveGame * Load begin
    - Game_LoadEnd_SaveGame   *
  */

#define AppDefault True
  CApplication* lpApplication = !CHECK_THIS_ENGINE ? Null : CApplication::CreateRefApplication(
    Enabled( AppDefault ) Game_Entry,
    Enabled( AppDefault ) Game_Init,
    Enabled( AppDefault ) Game_Exit,
    Enabled( AppDefault ) Game_PreLoop,
    Enabled( AppDefault ) Game_Loop,
    Enabled( AppDefault ) Game_PostLoop,
    Enabled( AppDefault ) Game_MenuLoop,
    Enabled( AppDefault ) Game_SaveBegin,
    Enabled( AppDefault ) Game_SaveEnd,
    Enabled( AppDefault ) Game_LoadBegin_NewGame,
    Enabled( AppDefault ) Game_LoadEnd_NewGame,
    Enabled( AppDefault ) Game_LoadBegin_SaveGame,
    Enabled( AppDefault ) Game_LoadEnd_SaveGame,
    Enabled( AppDefault ) Game_LoadBegin_ChangeLevel,
    Enabled( AppDefault ) Game_LoadEnd_ChangeLevel,
    Enabled( AppDefault ) Game_LoadBegin_Trigger,
    Enabled( AppDefault ) Game_LoadEnd_Trigger,
    Enabled( AppDefault ) Game_Pause,
    Enabled( AppDefault ) Game_Unpause,
    Enabled( AppDefault ) Game_DefineExternals,
    Enabled( AppDefault ) Game_ApplyOptions
  );
}