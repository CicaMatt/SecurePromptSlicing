import java.util.*;
import spark.ModelAndView;
import spark.template.handlebars.HandlebarsTemplateEngine;
import static spark.Spark.*;

public class Hello {
    
    public static void main(String[] args) {
        port(getHerokuAssignedPort());
        staticFileLocation("/public");
        get("/", (request, response) -> {
            Map<String, Object> model = new HashMap<>();
            model.put("name", request.queryParams(":name"));
            return render_response_from_env(model);
        });
    }
    
    private static String render_response_from_env(Map<String, Object> model) {
        return new HandlebarsTemplateEngine().render(new ModelAndView(model, "hello.hbs"));
    }
}