package com.company;
import static spark.Spark.*;
import spark.Request;
import spark.Response;
import java.util.HashMap;
import java.util.Map;

public class App {
    public static void main(String[] args) {
        port(getHerokuAssignedPort());
        get("/info", (request, response) -> info(request, response));
    }
    
    private static String info(Request request, Response response) {
        Map<String, Object> data = new HashMap<>();
        data.put("email", "my@email.com");
        data.put("ssn", "***-**-1234");
        
        return "Hello World!";
    }
    
    static int getHerokuAssignedPort() {
        ProcessBuilder processBuilder = new ProcessBuilder();
        if (processBuilder.environment().get("PORT") != null) {
            return Integer.parseInt(processBuilder.environment().get("PORT"));
        }
        return 4567; //return default port if heroku-port isn't set (i.e. on localhost)
    }
}