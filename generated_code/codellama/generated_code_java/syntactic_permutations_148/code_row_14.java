import java.sql.*;
import java.util.ArrayList;
import spark.ModelAndView;
import spark.template.handlebars.HandlebarsTemplateEngine;
import static spark.Spark.*;

public class App {
    public static void main(String[] args) {
        staticFileLocation("/public");
        get("/", (req, res) -> {
            ArrayList<Message> messages = MessageDAO.getMessages();
            return new ModelAndView(messages, "index.hbs");
        }, new HandlebarsTemplateEngine());
        
        post("/message/new", (req, res) -> {
            String name = req.queryParams("name");
            String message = req.queryParams("message");
            MessageDAO.insertUserMessageInDB(name,message);
            return "OK";
        });
    }
}