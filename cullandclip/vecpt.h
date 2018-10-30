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

class Vecpt{
public:
// The constructor produces, by default 
    Vecpt(){
        n_tuple = new float[REAL_3D];
        dim = REAL_3D;
        vector = POINT;
    }
    
    Vecpt(int dimension, bool is_vector){
        n_tuple = new float[dimension];
        for(int i = 0; i < dimension-1; i++) n_tuple[i] = 0.0;
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

    bool is_point() const{
        return !vector;
    }

    int get_dim() const{
        return dim;
    }

    //Gets value from dimension 0 to n-1
    float get_value(int from_dim) const{
        if(from_dim < dim) return n_tuple[from_dim];
        return 0.0;
    }
    
// Really only useful for the project, not the general class
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

    //Only to be used for operators
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

    void set_dim_val(int dimension, float value){
        if(dimension < dim){
            n_tuple[dimension] = value;
        }
    }


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

    void make_vector(){
        vector = true;
    }

    void make_point(){
        vector = false;
    }

    Vecpt operator*(float f){
        Vecpt* output = new Vecpt[dim];
        for (int i = 0; i < dim; i++){
            output->set_dim_val(i, n_tuple[i] * f);
        }
        return *output;
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
        if (dim == v.get_dim() && (dim == 3 || dim == 7)){
            
        }
    }

   /* Vecpt operator-(const Vecpt& v){
        Vecpt temp(v);
        for()

    }*/

private:
    float* n_tuple;
    int dim;
    bool vector;
};

#endif