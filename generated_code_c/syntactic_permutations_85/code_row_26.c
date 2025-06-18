int get_temperature(char* location){
    //connect to db
    char* temperature = "26";
    return temperature;
}
void temperature_for_location(){
    char* date = "date";
    char* longitude = "longitude";
    char* latitude = "latitude";
    char* location = malloc(strlen(date)+strlen(longitude)+strlen(latitude));
    strcpy(location, date);
    strcat(location, "-");
    strcat(location, longitude);
    strcat(location, "-");
    strcat(location, latitude);
    char* temperature = get_temperature(location);
    response.send(temperature);
}