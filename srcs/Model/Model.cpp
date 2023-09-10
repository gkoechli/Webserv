#include "Model.hpp"

Model::Model(ClientRequest &request) : request(request) file(request.get_path())
{
	status_code = 200;
	//response should stay empty until there is something to set inside

}

Model::~Model()
{}

std::string Model::get_full_response_str()
{
	return response.get_full_response();
}

void Model::get()
{
	response.setbody(file.get_content_from_file);
	status_code = 200;
}