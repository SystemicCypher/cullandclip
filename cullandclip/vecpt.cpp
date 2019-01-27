#include "vecpt.h"

// Constructors and Destructors

Vecpt::Vecpt(){
        n_tuple = new float[REAL_3D];
        for(int i = 0; i < REAL_3D; i++) n_tuple[i] = NAN;
        dim = REAL_3D;
        vector = POINT;
    }

Vecpt::Vecpt(int dimension, bool is_vector){
        n_tuple = new float[dimension];
        for(int i = 0; i < dimension; i++) n_tuple[i] = NAN;
        dim = dimension;
        vector = is_vector;
    }

Vecpt::Vecpt(const Vecpt& copy){
        dim = copy.get_dim();
        n_tuple = new float[dim];
        vector = (copy.is_point() ? POINT : VECTOR);
        for(int i = 0; i < dim; i++){
            n_tuple[i] = copy.get_value(i);
        } 
    }

Vecpt::~Vecpt(){
        delete n_tuple;
    }

// Class Methods

bool Vecpt::is_point() const{
        return !vector;
    }

bool Vecpt::is_vector() const{
        return vector;
    }

int Vecpt::get_dim() const{
        return dim;
    }

float Vecpt::get_value(int from_dim) const{
        if(from_dim < dim) return n_tuple[from_dim];
        return NAN;
    }

void Vecpt::add_dim(){
        int new_dim = dim + 1;
        bool new_vector = !(this->is_point());
        float* new_vec = new float[new_dim];
        for(int i = 0; i < dim; i++){
            new_vec[i] = n_tuple[i];
        }
        new_vec[dim] = 0.0;
        dim = new_dim;
        float* temp = n_tuple;
        n_tuple = new_vec;
        delete temp;
    }

void Vecpt::set_dim_val(int dimension, float value){
        if(dimension < dim){
            n_tuple[dimension] = value;
        }
    }

void Vecpt::make_vector(){
        vector = true;
    }

void Vecpt::make_point(){
        vector = false;
    }

// Operator Overloads

Vecpt Vecpt::operator+(const Vecpt& v) {
        Vecpt* output;
		if(v.get_dim() == dim){
            output = (vector == !(v.is_point())) ? new Vecpt(dim, VECTOR) : new Vecpt(dim, POINT);
            for(int i = 0; i < dim; i++){
                output->set_dim_val(i, n_tuple[i] + v.get_value(i));
            }
            return *output;
        }
        else{
            int selected_dim = (dim > v.get_dim()) ? dim : v.get_dim();
            output = (vector == !(v.is_point())) ? new Vecpt(selected_dim, VECTOR) : new Vecpt(selected_dim, POINT);
            
            if(dim == selected_dim){
                for(int i = 0; i < v.get_dim(); i++){
                    output->set_dim_val(i, n_tuple[i] + v.get_value(i));
                }
                for(int i = v.get_dim(); i < dim; i++){
                    output->set_dim_val(i, n_tuple[i]);
                }
            }
            else{
                for(int i = 0; i < dim; i++){
                    output->set_dim_val(i, n_tuple[i] + v.get_value(i));
                }
                for(int i = dim; i < v.get_dim(); i++){
                    output->set_dim_val(i, v.get_value(i));
                }
            }

            return *output;
        }
	}

    Vecpt Vecpt::operator-(const Vecpt& v){
        Vecpt* output;
		if(v.get_dim() == dim){
            output = (vector == !(v.is_point())) ? new Vecpt(dim, VECTOR) : new Vecpt(dim, POINT);
            for(int i = 0; i < dim; i++){
                output->set_dim_val(i, n_tuple[i] - v.get_value(i));
            }
            return *output;
        }
        else{
            int selected_dim = (dim > v.get_dim()) ? dim : v.get_dim();
            output = (vector == !(v.is_point())) ? new Vecpt(selected_dim, VECTOR) : new Vecpt(selected_dim, POINT);
            
            if(dim == selected_dim){
                for(int i = 0; i < v.get_dim(); i++){
                    output->set_dim_val(i, n_tuple[i] - v.get_value(i));
                }
                for(int i = v.get_dim(); i < dim; i++){
                    output->set_dim_val(i, n_tuple[i]);
                }
            }
            else{
                for(int i = 0; i < dim; i++){
                    output->set_dim_val(i, n_tuple[i] - v.get_value(i));
                }
                for(int i = dim; i < v.get_dim(); i++){
                    output->set_dim_val(i, v.get_value(i));
                }
            }

            return *output;
        }
    }

    void Vecpt::operator=(const Vecpt &v) {
        float* temp = n_tuple;
        float* output = new float[v.get_dim()];

        for(int i = 0; i < v.get_dim(); i++){
            output[i] = v.get_value(i);
        }
        dim = v.get_dim();
        vector = !(v.is_point());
        n_tuple = output;
        delete temp;
	}

    Vecpt Vecpt::operator*(float f){
        Vecpt* output = new Vecpt(dim, vector);
        for (int i = 0; i < dim; i++){
            output->set_dim_val(i, n_tuple[i] * f);
        }
        return *output;
    }

    Vecpt Vecpt::operator/(float f){
        Vecpt* output = new Vecpt(dim, vector);
        for (int i = 0; i < dim; i++){
            output->set_dim_val(i, n_tuple[i] / f);
        }
        return *output;
    }

    bool Vecpt::operator==(const Vecpt& v){
        bool output;
        output =  (dim == v.get_dim()) && (vector == v.is_vector());
        if(!output) return false;
        for(int i = 0; i < dim; i++){
            if(n_tuple[i] != v.get_value(i)) return false;
        }
        return true;

    }

    float Vecpt::operator[](int index){
        if(index >= dim){
            throw std::out_of_range("Out of Bounds: Accessing dimension that does not exist\n");
        }
        return n_tuple[index];
    }

// Vector Operations

float Vecpt::dot(const Vecpt& v){
        float output = 0;
        if(dim == v.get_dim()){
            for(int i = 0; i < dim; i++){
                output += (n_tuple[i] * v.get_value(i));
            }
        }
        return output;
    }

Vecpt Vecpt::cross(const Vecpt& v){
        Vecpt* output;
        if (!vector || v.is_point()){
            output = new Vecpt(0, POINT);
            return *output;
        }
        else if (dim == v.get_dim() && (dim == 3)){
            float i = n_tuple[1] * v.get_value(2) - n_tuple[2] * v.get_value(1);
		    float j = n_tuple[0] * v.get_value(2) - n_tuple[2] * v.get_value(0);
		    float k = n_tuple[0] * v.get_value(1) - n_tuple[1] * v.get_value(0);

		    output = new Vecpt(3, VECTOR);
            output->set_dim_val(0, i);
            output->set_dim_val(1, -j);
            output->set_dim_val(2, k);

            return *output;
        }
        else{
            output = new Vecpt(0, POINT);
            return *output;
        }
    } 

float Vecpt::magnitude(){
        float sqrtMe = 0.0;
        for(int i = 0; i < dim; i++){
            sqrtMe += n_tuple[i] * n_tuple[i];
        }
        return sqrt(sqrtMe);
    }

Vecpt Vecpt::normalize(){
        Vecpt* output;
        float mag = magnitude();
        output = new Vecpt(dim, vector);
        for(int i = 0; i < dim; i++){
            output->set_dim_val(i, n_tuple[i] / mag);
        }
        return *output;
    }