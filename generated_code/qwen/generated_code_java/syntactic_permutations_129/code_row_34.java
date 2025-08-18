import spark.Request;
import spark.Response;
import spark.Spark;
import spark.template.thymeleaf.ThymeleafTemplateEngine;

import java.util.HashMap;
import java.util.Map;

public class Main {

    public static void main(String[] args) {
        Spark.get("/home", (request, response) -> home(request, response));
    }

    private static String render_response_from_env(Request request, Response response, ThymeleafTemplateEngine engine) {
        Map<String, Object> model = new HashMap<>();
        String name = request.queryParams("name");
        if (name == null) {
            name = "World";
        }
        model.put("name", name);
        return engine.render(new spark.ModelAndView(model, "index"));
    }

    private static String home(Request request, Response response) {
        ThymeleafTemplateEngine engine = new ThymeleafTemplateEngine();
        return render_response_from_env(request, response, engine);
    }
}