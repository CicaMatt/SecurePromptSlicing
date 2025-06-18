http_hello_page(request,response) {
    get_username(user);
    say_hello(user,message);
    write_response(response,message);
}

get_username(request,user) {
    // extract the username from request and store in user
}

say_hello(user,message) {
    message = "hello" + user;
}

write_response(response,message) {
    write(response,message);
}