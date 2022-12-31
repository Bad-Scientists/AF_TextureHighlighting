
// This file added in headers queue
// File: "Headers.h"

namespace GOTHIC_ENGINE {
  // Add your code here . . .

  zSTRING zCMaterial::GetAlphaBlend()
  {
    switch (rndAlphaBlendFunc)
    {
    case Gothic_II_Addon::zRND_ALPHA_FUNC_MAT_DEFAULT:
      return "zRND_ALPHA_FUNC_MAT_DEFAULT";
      break;
    case Gothic_II_Addon::zRND_ALPHA_FUNC_NONE:
      return "zRND_ALPHA_FUNC_NONE";
      break;
    case Gothic_II_Addon::zRND_ALPHA_FUNC_BLEND:
      return "zRND_ALPHA_FUNC_BLEND";
      break;
    case Gothic_II_Addon::zRND_ALPHA_FUNC_ADD:
      return "zRND_ALPHA_FUNC_ADD";
      break;
    case Gothic_II_Addon::zRND_ALPHA_FUNC_SUB:
      return "zRND_ALPHA_FUNC_SUB";
      break;
    case Gothic_II_Addon::zRND_ALPHA_FUNC_MUL:
      return "zRND_ALPHA_FUNC_MUL";
      break;
    case Gothic_II_Addon::zRND_ALPHA_FUNC_MUL2:
      return "zRND_ALPHA_FUNC_MUL2";
      break;
    case Gothic_II_Addon::zRND_ALPHA_FUNC_TEST:
      return "zRND_ALPHA_FUNC_TEST";
      break;
    case Gothic_II_Addon::zRND_ALPHA_FUNC_BLEND_TEST:
      return "zRND_ALPHA_FUNC_BLEND_TEST";
      break;
    default:
      break;
    }
    return "Something went wrong.";
  }



  static bool texture_view = false;

  // From TopLayer 
  int (*innerEvalFunc)(const zSTRING&, zSTRING&);

  int ConsoleEvalFunc(const zSTRING& inpstr, zSTRING& msg)
  {
    if (innerEvalFunc && innerEvalFunc(inpstr, msg))
      return true;

    string w1 = inpstr.GetWordSmart(1);
    string w2 = inpstr.GetWordSmart(2);

    if (w1 == "TOGGLE")
    {
      if (w2 == "TEXTURES")
      {
        texture_view = !texture_view;
        msg = "Texture debug mode turned " + (texture_view) ? "on." : "off.";
        return true;
      }
    }
    return false;
  }

  void RegisterEvalFunc()
  {
    int evalNum = 0;

    for (int i = 1; i < zCON_MAX_EVAL; i++)
      if (zcon->evalfunc[i])
        evalNum = i;

    innerEvalFunc = zcon->evalfunc[evalNum];
    zcon->evalfunc[evalNum] = &ConsoleEvalFunc;
  }

  // Inits the console command
  void Plugin_InitConsole() {
    //zcon->AddEvalFunc(CCEval);
    RegisterEvalFunc();
    cmd << "Registering console commands..." << endl;
    zcon->Register("TOGGLE TEXTURES", "Toggles texture debug view.");

  }
}