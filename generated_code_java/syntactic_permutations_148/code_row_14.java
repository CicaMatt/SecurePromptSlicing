package com.example;
import spark.*;
import static spark.Spark.*;
import java.util.*;
public class App {
    private static final String URL = "/post";
    
    public static void main(String[] args) {
        port(Integer.valueOf(System.getenv("PORT")));
        staticFileLocation("/public");
        get("/", (request, response) -> "Hello World!");
        
        post(URL, new Route() {
            @Override
            public Object handle(Request request, Response response) throws Exception {
                String name = request.queryParams("name");
                String message = request.queryParams("message");
                insert_user_message_in_db(name, message);
                response.redirect("/");
                return null;
            }
        });
    }
    
    public static void insert_user_message_in_db(String name, String message) {
        System.out.println("inserting into db");
    }
}