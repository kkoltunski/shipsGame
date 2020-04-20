2020.02.14
-Tship class is updated of virtual destructor - it is helpful for ships destructor calls in Tboard::~Tboard() 
-static_casts<>() translations in Tboard::CreateShip function are deleted - were not necessary for Ships vector push_back()