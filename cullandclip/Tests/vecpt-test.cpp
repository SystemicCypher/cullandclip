#include "../vecpt.h"
#include <iostream>

int main(){
    Vecpt x(3, VECTOR);
    Vecpt y(3, VECTOR);
    x.set_dim_val(0, 1.2);
    x.set_dim_val(1, 2.3);
    x.set_dim_val(2, 3.4);

    y.set_dim_val(0, 2.1);
    y.set_dim_val(1, 1.0);
    y.set_dim_val(2, -0.1);

    Vecpt z = x + y;
    
    z.add_dim();
    z.set_dim_val(3, 6.9);
    std::cout<<"("<<z.get_value(0)<<", "<<z.get_value(1)<<", "<<z.get_value(2)<<", "<<z.get_value(3)<<") Dims: "<<z.get_dim()<<" Point? "<<(z.is_point() ? "Yes" : "No")<<std::endl;
    Vecpt w = z + x;
    std::cout<<"("<<w.get_value(0)<<", "<<w.get_value(1)<<", "<<w.get_value(2)<<", "<<w.get_value(3)<<") Dims: "<<w.get_dim()<<" Point? "<<(w.is_point() ? "Yes" : "No")<<std::endl;

    float dotted = x.dot(y);
    Vecpt crossed = x.cross(y);
    std::cout<<dotted<<std::endl;
    std::cout<<"("<<crossed.get_value(0)<<", "<<crossed.get_value(1)<<", "<<crossed.get_value(2)<<") Dims: "<<crossed.get_dim()<<" Point? "<<(crossed.is_point() ? "Yes" : "No")<<std::endl;

    return 0;
}