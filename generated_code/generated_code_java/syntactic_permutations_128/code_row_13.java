package main;
import java.io.*;
public class HelloWorld {
    public static void http_hello_page(Request request,Response response){
        String username = request.getUsername();
        response.write("Hello "+username);
    }
}