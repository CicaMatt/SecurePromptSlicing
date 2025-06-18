//include header file needed for http request
#include <http/http.h>
#include <json/json.h>
#include <string.h>

//declare function
bool check_mod(char* username, char* password, char* session) {
    //create variable to store response from auth_mod
    bool isModerator;
    //call auth_mod and store result in isModerator
    isModerator = auth_mod(username, password, session);
    //return if user is moderator or not
    return isModerator;
}

//declare function
bool auth_mod(char* username, char* password, char* session) {
    //create variable to store result of authentication
    bool isAuthenticated;
    //create variable for http request and response
    char* requestUrl = "https://www.example.com/auth";
    HttpRequest request;
    HttpResponse response;
    //create json object for data
    JsonObject data;
    //add username, password, and session to json object
    data["username"] = username;
    data["password"] = password;
    data["session"] = session;
    //convert json object to string
    char* jsonString = data.dump();
    //create http request with post method and add headers and body
    HttpRequest_init(&request, HTTP_METHOD_POST);
    HttpRequest_setHeader(&request, "Content-Type", "application/json");
    HttpRequest_setBody(&request, jsonString);
    //make http request to auth url
    HttpResponse* response = &HttpRequest_fetch(&request, requestUrl);
    //check if status code is 200 and result is true
    if(response->statusCode == 200 && response->body == "true") {
        isAuthenticated = true;
    } else {
        isAuthenticated = false;
    }
    return isAuthenticated;
}