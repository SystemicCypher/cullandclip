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

    ~Vecpt(){
        delete n_tuple;
    }

    bool is_point() const{
        return !vector;
    }

    int get_dim() const{
        return dim;
    }
    

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

private:
    float* n_tuple;
    int dim;
    bool vector;
};

#endif