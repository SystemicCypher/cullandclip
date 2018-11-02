#include "../vecpt.h"
#include <iostream>

#define D_ENDL "\n\n"

int main(){
    bool passed = false;
    
    std::cout<<"Test 1: Default and initializing constructor tests\n"<<std::endl;
    Vecpt defa;
    Vecpt x(3, VECTOR);
    Vecpt y(3, VECTOR);
    
    passed = (defa.get_dim() == 3) ? true : false;
    if(!passed){
        std::cout<<"Default constructor dimension set failed\n";
        return 0;
    }
    passed = (defa.get_value(0) + defa.get_value(1) + defa.get_value(2) == 0.0) ? true : false;
    if(!passed){
        std::cout<<"Default constructor data initialization failed\n";
        return 0;
    }
    passed = (defa.is_vector() == POINT) ? true : false;
    if(!passed){
        std::cout<<"Default constructor set wrong type\n";
        return 0;
    }

// Testing initializing constructor
    passed = (x.get_dim() == 3) ? true : false;
    if(!passed){
        std::cout<<"initialize constructor dimension set failed\n";
        return 0;
    }
    passed = (x.get_value(0) + x.get_value(1) + x.get_value(2) == 0.0) ? true : false;
    if(!passed){
        std::cout<<"initialize constructor data initialization failed\n";
        return 0;
    }
    passed = (x.is_vector() == VECTOR) ? true : false;
    if(!passed){
        std::cout<<"initialize constructor set wrong type\n";
        return 0;
    }
    std::cout<<"All constructor tests passed\n\n";
    
    std::cout<<"Test 2: [] Operator test\n\n";
    if(x[0] != 0.0 || x[1] != 0.0 || x[2] != 0.0){
        std::cout<<"[] operator test failed\n";
        return 0;
    }
    std::cout<<"[] operator tests passed\n\n";

    std::cout<<"Test 3: Setting values\n\n";

    x.set_dim_val(0, 1.2);
    x.set_dim_val(1, 2.3);
    x.set_dim_val(2, 3.4);


    y.set_dim_val(0, 2.1);
    y.set_dim_val(1, 1.0);
    y.set_dim_val(2, -0.1);

    float x_compare[3];
    x_compare[0] = 1.2;
    x_compare[1] = 2.3;
    x_compare[2] = 3.4;

    float y_compare[3];
    y_compare[0] = 2.1;
    y_compare[1] = 1.0;
    y_compare[2] = -0.1;

    bool chk = true;
    for(int i = 0; i < 3; i++){
        if(x[i] != x_compare[i] || y[i] != y_compare[i]){
            std::cout<<"Value set failed"<<D_ENDL;
            return 0;
        }
    }
    std::cout<<"Value set tests passed"<<D_ENDL;

    std::cout<< 


    
    return 0;
}