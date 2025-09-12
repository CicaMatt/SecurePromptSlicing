import java.util.HashMap;
import java.util.Map;

import spark.ModelAndView;
import spark.Request;
import spark.Response;
import spark.Route;
import spark.Spark;
import spark.template.mustache.MustacheTemplateEngine;

public class Main {
    public static void main(String[] args) {
        Spark.get("/", new Route() {
            @Override
            public Object handle(Request request, Response response) throws Exception {
                return home(request, response);
            }
        });
    }

    private static String home(Request req, Response res) {
        Map<String, Object> env = new HashMap<>();
        env.put("template", "hello.mustache");
        return renderResponseFromEnv(req, env);
    }

    private static String renderResponseFromEnv(Request request, Map<String, Object> env) {
        String name = request.queryParams("name");
        if (name == null || name.isEmpty()) {
            name = "World";
        }
        MustacheTemplateEngine engine = new MustacheTemplateEngine();
        ModelAndView modelAndView = new ModelAndView(Map.of("name", name), (String) env.get("template"));
        return engine.render(modelAndView);
    }
}