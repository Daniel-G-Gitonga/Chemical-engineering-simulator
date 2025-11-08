#include "app.h"
#include "DEFINITIONS/def.h"
#include <glad/glad.h>


struct Model{
    std::string path_to_model;
    glm::vec3 pos;
    std::string id;
};
Model pass_model_info(std::string path, glm::vec3 position, std::string id){
    Model model;
    model.path_to_model = path;
    model.pos = position;
    model.id  = id;

    return model;
    }
int main(int argc, char ** argv){
chem::mess("Hello world , my nmae is daniel G and I am no one intresting \n \n anyways how are you \n\n HELLO FRIEND 😂");
chem::mess("current working dirrectory==> ");
std::cout<<argv[0]<<std::endl;    
 
///
///loading data here
std::vector<Model> passed_data;
//function thet will be pushed into the vector
passed_data.push_back(pass_model_info("../../Assets/model/abcd.gltf",glm::vec3(0.0f,2.0f,  0.0f ), "Unique_box_test"));
//passed_data.push_back(pass_model_info("../../Assets/model/HOUSE.gltf",glm::vec3(0.0f,2.0f,-4.0f)));
///


chem::App * sandBox = new chem::App("The Chemical Engineering SandBox",800,700);



std::vector<std::string> paths_loaded_from_model;
std::vector<glm::vec3>  position_loaded_from_model;
std::vector<std::string> specific_id_of_model;

//process the vector containing model array and pass the path and position the 
    //respective vector for use as arguments
    for(int i=0; i<passed_data.size() ; i++){
paths_loaded_from_model.push_back(passed_data[i].path_to_model);
position_loaded_from_model.push_back(passed_data[i].pos);
specific_id_of_model.push_back(passed_data[i].id);
    }

sandBox->set_model_array(paths_loaded_from_model, position_loaded_from_model, specific_id_of_model);
sandBox->setup();



if(sandBox->is_window_ready){
   
       
       sandBox->run();
       //debug...:::...purpose
       std::cout<<" \n window is created  ? "<<sandBox->is_window_ready<<std::endl;

    
}else{
    std::cout<<"THERE IS NO WINDOW AVAILABLE ... ::: ... CHECK THE WINDOW FILE"<<std::endl;
}

delete sandBox;

}
//run app using C:\Users\USER\Desktop\ChemicalEngineeringStuff\build\sandBox\sandBox.exe
//able to set color, pos of light and timestamp...