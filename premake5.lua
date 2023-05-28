-- premake5.lua
workspace "AutoClicker"
   architecture "x64"
   configurations { "Debug", "Release", "Dist" }
   startproject "AutoClicker"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
include "Walnut/WalnutExternal.lua"

include "AutoClicker"