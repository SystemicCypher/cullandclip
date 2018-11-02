/*
* A multidimensional vector/point class
* There should probably be a separate point class that interacts with vectors.
*/

#ifndef VECPT_H
#define VECPT_H

// Basic sizes for the point/vector class
// This is intended to map 3D points and vectors to 4D homogeneous 
// points and vectors for simpler math.
#define HOMOGENEOUS 4
#define REAL_3D 3
#define REAL_2D 2

// Other fun macros - defines vector and point for the 
// vector and point boolean
#define VECTOR true
#define POINT false

#include <math.h>
#include <stdexcept>

class Vecpt{
public:
// The constructor produces, by default a real 3D point
    Vecpt(){
        n_tuple = new float[REAL_3D];
        for(int i = 0; i < REAL_3D; i++) n_tuple[i] = 0.0;
        dim = REAL_3D;
        vector = POINT;
    }
// If you wish to set the dimension and whether it's a vector or a point
    Vecpt(int dimension, bool is_vector){
        n_tuple = new float[dimension];
        for(int i = 0; i < dimension; i++) n_tuple[i] = 0.0;
        dim = dimension;
        vector = is_vector;
    }

    Vecpt(const Vecpt& copy){
        dim = copy.get_dim();
        n_tuple = new float[dim];
        vector = (copy.is_point() ? POINT : VECTOR);
        for(int i = 0; i < dim; i++){
            n_tuple[i] = copy.get_value(i);
        } 
    }

    ~Vecpt(){
        delete n_tuple;
    }
// Returns if the vecpt is a point or not - I'm considering using is_vector instead
    bool is_point() const{
        return !vector;
    }

    bool is_vector() const{
        return vector;
    }
//  Returns the dimensions of the vecpt
    int get_dim() const{
        return dim;
    }

//  Gets value from dimension 0 to n-1 -> basically a wrapper for n_tuple[i]
//  If it fails it will return "not a number"
    float get_value(int from_dim) const{
        if(from_dim < dim) return n_tuple[from_dim];
        return NAN;
    }
    
// Really only useful for the project, not the general class
// It will homogenize 3D points/vectors into 4D points/vectors
// <INCOMPLETE>
    static Vecpt homogenize4D(const Vecpt pt_vec){
        if(pt_vec.get_dim() == REAL_3D){
            Vecpt* output;
            switch(pt_vec.is_point()){
            case true:
                output = new Vecpt(4, POINT);
                break;

            case false:
                output = new Vecpt(4, VECTOR);
                break;

            default:
                output = new Vecpt();
                break;

            }
            return *output;
        }
    }

//  Only to be used for operators
//  Is likely to be deleted next iteration
    void add_dim(){
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

//  Sets dimension value, select a dimension, then the float value to insert
    void set_dim_val(int dimension, float value){
        if(dimension < dim){
            n_tuple[dimension] = value;
        }
    }

//  Overloaded + operator. Adds two vectors/points together. If pt + vec will return pt 
    Vecpt operator+(const Vecpt& v) {
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

    Vecpt operator-(const Vecpt& v){
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

    void operator=(const Vecpt &v) {
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

    void make_vector(){
        vector = true;
    }

    void make_point(){
        vector = false;
    }

    Vecpt operator*(float f){
        Vecpt* output = new Vecpt(dim, vector);
        for (int i = 0; i < dim; i++){
            output->set_dim_val(i, n_tuple[i] * f);
        }
        return *output;
    }

    Vecpt operator/(float f){
        Vecpt* output = new Vecpt(dim, vector);
        for (int i = 0; i < dim; i++){
            output->set_dim_val(i, n_tuple[i] / f);
        }
        return *output;
    }

    bool operator==(const Vecpt& v){
        bool output;
        output =  (dim == v.get_dim()) && (vector == v.is_vector());
        if(!output) return false;
        for(int i = 0; i < dim; i++){
            if(n_tuple[i] != v.get_value(i)) return false;
        }
        return true;

    }

    float operator[](int index){
        if(index >= dim){
            throw std::out_of_range("Out of Bounds: Accessing dimension that does not exist\n");
        }
        return n_tuple[index];
    }

    float dot(const Vecpt& v){
        float output = 0;
        if(dim == v.get_dim()){
            for(int i = 0; i < dim; i++){
                output += (n_tuple[i] * v.get_value(i));
            }
        }
        return output;
    }

    Vecpt cross(const Vecpt& v){
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

    float magnitude(){
        float sqrtMe = 0.0;
        for(int i = 0; i < dim; i++){
            sqrtMe += n_tuple[i] * n_tuple[i];
        }
        return sqrt(sqrtMe);
    }

    Vecpt normalize(){
        Vecpt* output;
        float mag = magnitude();
        output = new Vecpt(dim, vector);
        for(int i = 0; i < dim; i++){
            output->set_dim_val(i, n_tuple[i] / mag);
        }
        return *output;
    }


private:
    float* n_tuple;
    int dim;
    bool vector;
};

#endif