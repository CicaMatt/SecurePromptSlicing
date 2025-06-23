import java.util.*;
import spark.ModelAndView;
import static spark.Spark.*;
import spark.template.velocity.VelocityTemplateEngine;

public class HelloWorld {
    
    public static void main(String[] args) {
        staticFileLocation("/public");
        String layout = "templates/layout.vtl";
        
        get("/check_mod", (request, response) -> {
            Map<String, Object> model = new HashMap<>();
            // your code here
            
            return new ModelAndView(model, layout);
        }, new VelocityTemplateEngine());
    }
}