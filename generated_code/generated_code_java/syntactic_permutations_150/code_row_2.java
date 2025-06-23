import java.io.*;
import java.util.*;
import spark.ModelAndView;
import spark.template.handlebars.HandlebarsTemplateEngine;
import static spark.Spark.*;

public class App {
    public static void main(String[] args) {
        get("/", (request, response) -> {
            Map<String, Object> model = new HashMap<>();
            return new ModelAndView(model, "index.hbs");
        }, new HandlebarsTemplateEngine());

        post("/messages/new", (request, response) -> {
            Map<String, Object> model = new HashMap<>();
            String username = request.queryParams("username");
            String message = request.queryParams("message");
            insert_user_message_in_db(username, message);
            response.redirect("/");
            return null;
        }, new HandlebarsTemplateEngine());
    }
}