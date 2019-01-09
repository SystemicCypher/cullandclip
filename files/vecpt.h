//====================================
// Names:
// Austin Loza austinloza@csu.fullerton.edu
// Richard Ung rung921@csu.fullerton.edu
//====================================

/*
* --------------------------------------------------
* Vecpt (Vector - Point) Class
* --------------------------------------------------
* This is a generalized vector and point class. It is 
* scalable to any dimensional space though at present
* it has some functions that are limited to 3D/4D
*/

#ifndef VECPT_H
#define VECPT_H

/*
* --------------------------------------------------
* Dimension Abstractions
* --------------------------------------------------
* This is intended to map 3D points and vectors to 4D homogeneous 
* points and vectors for simpler math.
*/ 
#define HOMOGENEOUS 4
#define REAL_3D 3
#define REAL_2D 2

/*
* --------------------------------------------------
*   Vector / Point Abstraction
* --------------------------------------------------
* These define vector and point macros for the vector boolean value 
* in the class. It exists to make a bit more sense of true/false
* values returned and stored in this class.
*/
#define VECTOR true
#define POINT false

#include <math.h>
#include <stdexcept>

class Vecpt{
public:
/*
* --------------------------------------------------
* Constructors
* --------------------------------------------------
* Vecpt() : The default constructor creates a 3D point
* that contains NAN values for each of its components
*
* Vecpt(int dimension, bool is_vector) : This constructor
* creates a Vecpt with a defined dimension and sets it as
* a vector or point
*
* Vecpt(const Vecpt& copy) : This constructor allows for copying
* of an existing Vecpt
*/
    Vecpt();

    Vecpt(int dimension, bool is_vector);

    Vecpt(const Vecpt& copy);
/*
* --------------------------------------------------
* The DESTRUCTOR
* --------------------------------------------------
* Gets rid of the only dynamically allocated piece of
* junk I have this class create, the float* n_tuple
*/
    ~Vecpt();

/*
* --------------------------------------------------
* Vecpt Class Methods
* --------------------------------------------------
*/

/*
* --------------------------------------------------
* bool is_point
* --------------------------------------------------
* Description:
* A wrapper for accessing the vector boolean. It 
* provides an answer to the question...is this a 
* point? But that was obvious.
* --------------------------------------------------
* Input
* --------------------------------------------------
* Nothing...
* --------------------------------------------------
* Output
* --------------------------------------------------
* The opposite of the value of vector is returned
*/
    bool is_point() const;

/*
* --------------------------------------------------
* bool is_vector
* --------------------------------------------------
* Description:
* Read is_point above. The only difference is this 
* returns the value of vector unmodified.
*/
    bool is_vector() const;

/*
* --------------------------------------------------
* int get_dim
* --------------------------------------------------
* Description:
* A wrapper for accessing the dim integer. It returns 
* the dimension of the vector/point.
* --------------------------------------------------
* Input
* --------------------------------------------------
* Nothing...
* --------------------------------------------------
* Output
* --------------------------------------------------
* The dimension (dim) integer value. (the dimensionality of the Vecpt)
*/
    int get_dim() const;

/*
* --------------------------------------------------
* float get_value
* --------------------------------------------------
* Description:
* A wrapper for n_tuple[i]. It's better than that
* though because it prevents overaccess. It will 
* return NAN if the dimension that is requested from it
* is greater than the Vecpt's dimensionality
* --------------------------------------------------
* Input
* --------------------------------------------------
* int from_dim : The dimension of the tuple to get the value
* from. This is zero-indexed for array consistency. Please
* note that to access dimension 1, from_dim should be 0
* and so on.
* --------------------------------------------------
* Output
* --------------------------------------------------
* A floating point value from the dimension selected is 
* returned if such a dimension exists. If the dimension
* does not exist for that Vecpt, then NAN is returned.
*/
    float get_value(int from_dim) const;
    
//  Only to be used for operators
//  Is likely to be deleted next iteration
    void add_dim();

//  Sets dimension value, select a dimension, then the float value to insert
    void set_dim_val(int dimension, float value);

    void make_vector();

    void make_point();

// Operator overloads
//  Overloaded + operator. Adds two vectors/points together. If pt + vec will return pt 
    Vecpt operator+(const Vecpt& v);

    Vecpt operator-(const Vecpt& v);

    void operator=(const Vecpt &v);

    Vecpt operator*(float f);

    Vecpt operator/(float f);

    bool operator==(const Vecpt& v);

    float operator[](int index);

//Vector operations
    float dot(const Vecpt& v);

    Vecpt cross(const Vecpt& v);

    float magnitude();

    Vecpt normalize();

private:
    float* n_tuple;
    int dim;
    bool vector;
};

#endif