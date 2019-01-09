//====================================
// Names:
// Austin Loza austinloza@csu.fullerton.edu
// Richard Ung rung921@csu.fullerton.edu
//====================================

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <memory>
#include <utility>
#include "Camera.h"
#include "Object.h"
#include "Placement.h"
#include "triangle.h"
#include "vecpt.h"
#include "frsthelp.h"



//Note to self: all trailing \r characters have to be removed from the input files
int main(){
	std::string line;
	std::istringstream* splitter;
	
	Vecpt p0(REAL_3D, POINT);
	p0.set_dim_val(0, 0.0);
	p0.set_dim_val(1, 0.0);
	p0.set_dim_val(2, 0.0);

	std::vector<Object*> object_space;

	//Get first line
	getline(std::cin, line);
	if(line.find("model") != std::string::npos){
		while(line != ")"){
			getline(std::cin, line);

			if(line.find("( tri") != std::string::npos){
				//collect id
				splitter = new std::istringstream(line);
				std::string junk;
				int id;
				Vecpt p1(REAL_3D, POINT), p2(REAL_3D, POINT), p3(REAL_3D, POINT);
				float x, y, z;

				*splitter>>id;

				getline(std::cin, line);
				splitter = new std::istringstream(line);
				*splitter>>junk>>x>>y>>z;
				p1.set_dim_val(0, x);
				p1.set_dim_val(1, y);
				p1.set_dim_val(2, z);

				getline(std::cin, line);
				splitter = new std::istringstream(line);
				*splitter>>junk>>x>>y>>z;
				p2.set_dim_val(0, x);
				p2.set_dim_val(1, y);
				p2.set_dim_val(2, z);

				getline(std::cin, line);
				splitter = new std::istringstream(line);
				*splitter>>junk>>x>>y>>z;
				p3.set_dim_val(0, x);
				p3.set_dim_val(1, y);
				p3.set_dim_val(2, z);

				//           id regpt A  B   C
				Triangle* tri = new Triangle(id, p0, p1, p2, p3);
				object_space.push_back(tri);

			}

			else if(line.find("( camera") != std::string::npos){
				//collect all data
				splitter = new std::istringstream(line);
				std::string junk;
				int id, minsub, dmax;
				float w, h;
				*splitter>>id;
				*splitter>>junk>>junk>>junk>>minsub>>dmax>>w>>h;
				Camera* cam = new Camera(id, p0, w, h, minsub, dmax);
				object_space.push_back(cam);
			}
			
			else if(line.find("( bag") != std::string::npos){
				//collect id and data
				splitter = new std::istringstream(line);
				std::string junk;
				int id;
				float x, y, z, az, el;
				Vecpt regpt(REAL_3D, POINT);
				*splitter>>id>>junk>>junk>>junk>>x>>y>>z;
				regpt.set_dim_val(0, x);
				regpt.set_dim_val(1, y);
				regpt.set_dim_val(2, z);
				Object* obj = new Object(id, Kind::BAG, regpt);
				std::vector<KidLoc> kids;

				while(!(line.find(") ) )") != std::string::npos)){
					getline(std::cin, line);
					splitter = new std::istringstream(line);
					*splitter>>junk>>junk>>id>>junk>>junk>>junk>>x>>y>>z>>junk>>az>>el;
					Vecpt reggie(REAL_3D, POINT);
					reggie.set_dim_val(0, x);
					reggie.set_dim_val(1, y);
					reggie.set_dim_val(2, z);
					Placement place(reggie, az, el);
					KidLoc output(id, place);
					kids.push_back(output);
				}
				obj->setSubObjects(kids);
				object_space.push_back(obj);
			}
		}

	}

	//Move to the world space stuff
	getline(std::cin, line);

	std::vector<KidLoc> world_space;
	//Capture world space data
	while(line != ")"){
			getline(std::cin, line);
			splitter = new std::istringstream(line);
			std::string junk;
			int id;
			float x, y, z, az, el;
			*splitter>>junk>>junk>>id>>junk>>junk>>junk>>x>>y>>z>>junk>>az>>el;
			Vecpt point(REAL_3D, POINT);
			point.set_dim_val(0, x);
			point.set_dim_val(1, y);
			point.set_dim_val(2, z);
			Placement empl(point, az, el);
			KidLoc child(id, empl);
			world_space.push_back(child);
		}
	world_space.pop_back();

	// Initialization of basis vectors for the camera. 
	// Assumes D is looking right down the x-axis
	
	Vecpt D(REAL_3D, VECTOR), U(REAL_3D, VECTOR), R(REAL_3D, VECTOR);
	R.set_dim_val(0, 1.0);
	R.set_dim_val(1, 0.0);
	R.set_dim_val(2, 0.0);

	D.set_dim_val(0, 0.0);
	D.set_dim_val(1, 0.0);
	D.set_dim_val(2, 1.0);

	U.set_dim_val(0, 0.0);
	U.set_dim_val(1, 1.0);
	U.set_dim_val(2, 0.0);
	
	//This vector stores the triangles that have been rotated and translated
	//They're stored as triangles so that I can just run triangles through the
	//code I've got without having to worry to much about what bags they're in
	std::vector<Triangle> world_space_triangles;
	Camera* selected_cam;
	float dMin, dMax, width, height;
	Vecpt cam_location;
	Placement cam_rotation;
	
	for(auto& item : world_space){
		int id = item.first;
		Placement pl = item.second;
		for(auto& obj : object_space){
			if(obj->getObjectID() == id){
				//these are all bags - I have to go deeper than that
				for(auto& kid : obj->getKidsVec()){
					int sub_id = kid.first;
					Placement sub_pl = kid.second;
					
					for(auto& sub_item : object_space){
						if(sub_item->getObjectID() == sub_id){
							if(sub_item->getKindID() == Kind::TRIANGLE){
								Triangle *t_sub = dynamic_cast<Triangle*>(sub_item);
								Triangle t = frustrum::triangle_o2w(*t_sub, pl.ptReg, pl.azimuth, pl.elevation);
								
								world_space_triangles.push_back(t);
							}
							else if(sub_item->getKindID() == Kind::CAMERA){
								selected_cam = dynamic_cast<Camera*>(sub_item);
								dMin = selected_cam->get_minSubPt();
								dMax = selected_cam->get_dMax();
								width = selected_cam->get_width();
								height = selected_cam->get_height();
								cam_location = frustrum::object_to_world(sub_pl.ptReg, pl.ptReg, pl.azimuth, pl.elevation);
								cam_rotation = pl;					
								
							}

							break;
						}
					}
				}
				break;
			}
		}	 
	}

	

	std::vector<Triangle> view_space_triangles;
	for(auto& tri : world_space_triangles){
		Triangle t_out = frustrum::triangle_w2c(tri, cam_location*-1, -1*cam_rotation.azimuth, -1*cam_rotation.elevation);	
		view_space_triangles.push_back(t_out);
	} 

	std::vector<Triangle> projected_tris;
	for(auto& tri : view_space_triangles){
		Triangle t_out = frustrum::triangle_project(tri, dMin, dMax, width, height);
		projected_tris.push_back(t_out);
	}

	//Time for output!
	for(auto& tri : projected_tris){
		std::pair<int, frustrum::Verdict> end = frustrum::cullandclip(tri);
		if(end.second == frustrum::Verdict::TRI){
			std::cout<<"Triangle "<<tri.getObjectID()<<"\n";
		}
		else if(end.second == frustrum::Verdict::CULL){
			std::cout<<"Triangle "<<tri.getObjectID()<<" CULLED\n";
		}
		else{
			std::cout<<"Triangle "<<tri.getObjectID()<<" CLIPPED\n";
		}
	}
	return 0;
}
