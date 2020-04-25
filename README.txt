2020.02.14
-Tship class is updated of virtual destructor - it is helpful for ships destructor calls in Tboard::~Tboard() 
-static_casts<>() translations in Tboard::CreateShip function are deleted - were not necessary for Ships vector push_back()

2020.04.20
-completely rebuilded software (after i learned full c++ possibilities i decide to refactore this software)
-there is a bug in file userDataInterface.cpp - line 143 do...while loop - user is asked about ship type two times
i dont know why but in Dev-C++ it worked as i except and maybe it is VisualStudio compiler bug?

2020.04.24
-Comments update for doxygen
-Folder "Doxygen" include documentation

2020.04.25 
-Code rewiev with static analyse tool cppcheck.
-Magic numbers - groupping and cleaning.