import java.util.*;
import spark.ModelAndView;
import spark.template.handlebars.HandlebarsTemplateEngine;

public class HelloWorld {
    static String render_response_from_env(Environment env) {
        Request request = env.request();
        Map<String, Object> model = new HashMap<>();
        model.put("name", request.params(":name"));
        Template template = env.loadTemplate("Hello");
        return new ModelAndView(model, "Hello"), HandlebarsTemplateEngine).render();
    }

    public static void main(String[] args) {
        Get("/hello/:name", (request, response) -> render_response_from_env(request.raw()));
    }
}