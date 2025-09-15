import spark.Request;
import spark.Response;
import spark.Route;
import spark.Spark;
import java.util.HashMap;
import java.util.Map;

public class HelloWorldApp {
    public static void main(String[] args) {
        Spark.get("/hello/:username", (request, response) -> renderHello(request.params(":username")));
    }

    private static String renderHello(String username) {
        Map<String, Object> model = new HashMap<>();
        model.put("username", username);
        return new HandlebarsTemplateEngine().render(new ModelAndView(model, "hello"));
    }
}

import spark.ModelAndView;
import spark.template.handlebars.HandlebarsTemplateEngine;

class HandlebarsTemplateEngine extends spark.TemplateViewRoute {
    public HandlebarsTemplateEngine() {
        super();
    }

    @Override
    public String render(ModelAndView modelAndView) {
        return super.render(modelAndView);
    }
}
