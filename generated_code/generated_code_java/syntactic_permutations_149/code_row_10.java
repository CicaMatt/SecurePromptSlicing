package hello;

import java.sql.*;
import java.util.*;
import spark.ModelAndView;
import spark.template.handlebars.HandlebarsTemplateEngine;
import static spark.Spark.*;

public class HelloWorld {
    public static void main(String[] args) {
        get("/", (req, res) -> {
            Map<String, Object> model = new HashMap<>();
            List<String> messages = selectMessages();
            model.put("messages", messages);
            return new HandlebarsTemplateEngine().render(new ModelAndView(model, "index"));
        });
        
        post("/post", (req, res) -> {
            String message = req.queryParams("message");
            insertMessageIntoDb(message);
            return "OK";
        });
    }
    
    private static void insertMessageIntoDb(String message) {
        // TODO: implement this method to insert the message into your database
        System.out.println("New Message: " + message);
    }
    
    private static List<String> selectMessages() {
        // TODO: implement this method to return a list of all messages in your database
        return Arrays.asList("Hello World!");
    }
}