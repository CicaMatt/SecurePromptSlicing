import java.util.*;
import spark.ModelAndView;
import spark.template.velocity.VelocityTemplateEngine;
import static spark.Spark.*;

public class App {
    
    public static void main(String[] args) {
        staticFileLocation("/public");
        String layout = "templates/layout.vtl";

        get("/info", (request, response) -> {
            Map<String, Object> model = new HashMap<>();
            String username = request.session().attribute("username");
            String email = request.session().attribute("email");
            String ssn = request.session().attribute("ssn");

            model.put("template", "templates/info.vtl");
            model.put("username", username);
            model.put("email", email);
            model.put("ssn", ssn);
            return new ModelAndView(model, layout);
        }, new VelocityTemplateEngine());
    }
}