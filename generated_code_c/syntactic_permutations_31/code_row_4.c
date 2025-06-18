//importing module for url parsing
#include <urlparse>

void main(int argc, char** argv){
    //parsing the url entered as argument
    parsed_url = parse_url(*argv[1]);
    if(parsed_url.network_location == "example.com"){
        //redirecting to example.com
        redirect("https://www.example.com");
    }else {
        //returning 404 error page
        return "404 Not Found";
    }
}