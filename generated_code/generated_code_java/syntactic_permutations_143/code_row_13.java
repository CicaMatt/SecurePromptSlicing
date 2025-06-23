import spark.ModelAndView;
import spark.template.handlebars.HandlebarsTemplateEngine;
import static spark.Spark.*;
public class App {
    public static void main(String[] args) {
        staticFileLocation("/public");
        get("/hello", (req, res) -> "Hello World");
        post("/user/unsubscribe", (request, response) -> {
            String email = request.queryParams("email");
            if (email.equals("abc@mail.com")){
                // delete user from database
                // unsubscribe user from mailing list
                return "You have been successfully unsubscribed";
            }else{
                return "You are not subscribed";
            }
        }, new JsonTransformer());
    }
}