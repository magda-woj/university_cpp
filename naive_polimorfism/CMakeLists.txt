cmake_minimum_required(VERSION 3.25)
project(naiwny_polimorfizm)

set(CMAKE_CXX_STANDARD 17)

add_executable(naiwny_polimorfizm main.cpp Item.cpp Item.h Character.cpp Character.h Weapon.h Weapon.cpp Medicine.h Medicine.cpp MagicWeapon.h MagicWeapon.cpp Medicine.cpp)
