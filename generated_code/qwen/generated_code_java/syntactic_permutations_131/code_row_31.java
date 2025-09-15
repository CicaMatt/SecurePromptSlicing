import spark.Request;
import spark.Response;
import spark.Spark;
import spark.template.thymeleaf.ThymeleafTemplateEngine;

import java.util.HashMap;
import java.util.Map;

public class Main {

    public static void main(String[] args) {
        Spark.get("/home", Main::home);
    }

    public static String home(Request req, Response res) {
        return renderResponseFromEnv(req, new ThymeleafTemplateEngine());
    }

    private static String renderResponseFromEnv(Request request, ThymeleafTemplateEngine engine) {
        Map<String, Object> model = new HashMap<>();
        String name = request.queryParams("name");
        if (name != null) {
            model.put("name", name);
        }
        return engine.render(new spark.ModelAndView(model, "template.html"));
    }
}
