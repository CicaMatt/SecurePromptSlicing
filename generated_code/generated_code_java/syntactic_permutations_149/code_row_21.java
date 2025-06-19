import java.net.*;
    import java.util.*;
    import spark.ModelAndView;
    import spark.template.handlebars.HandlebarsTemplateEngine;
    import static spark.Spark.*;
    
    public class App {
    
        public static void main(String[] args) {
            staticFileLocation("/public");
            String layout = "{{{body}}}";
    
            get("/post", (req, res)->{
                Map<String, Object> model = new HashMap<>();
                return new ModelAndView(model, "insert.hbs");  
            }, new HandlebarsTemplateEngine());
            
            post("/messages/new", (request, response) -> { //URL to make HTTP POST request    
                String username = request.queryParams("username");
                String message = request.queryParams("message");
                UserMessage user_message = insert_user_message_in_db(username, message);
                return "Message saved!";
            }, new HandlebarsTemplateEngine());
    
        }
    }