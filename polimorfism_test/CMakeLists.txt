cmake_minimum_required(VERSION 3.25)
project(oceniacz_testow)

set(CMAKE_CXX_STANDARD 17)

add_executable(oceniacz_testow main.cpp Pytanie.cpp Pytanie.h Oceniacz.cpp Oceniacz.h OceniaczPojedynczyWybor.cpp OceniaczPojedynczyWybor.h OceniaczWielokrotnyWybor.cpp OceniaczWielokrotnyWybor.h Test.cpp Test.h Person.cpp Person.h Oceniacz.h)
