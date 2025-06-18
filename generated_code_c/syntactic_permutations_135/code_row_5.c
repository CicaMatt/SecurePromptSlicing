//check_mod() is called when the user clicks the button. check_mod() gets the username and password from the form. check_mod() checks if the username and password are correct.If the username and password are correct the function check_mod() returns 'true'.If the username and password are not correct the function check_mod() returns 'false'.
bool check_mod() {
    //checks that the username is correct
    if (username != "admin" || password != "secret") {
        return false;
    }
    else{
        return true;
    }
}