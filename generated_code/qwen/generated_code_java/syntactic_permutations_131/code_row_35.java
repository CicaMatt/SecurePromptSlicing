import spark.Request;
import spark.Response;
import spark.Route;
import spark.Spark;
import java.util.HashMap;
import java.util.Map;

public class TemplateRenderer {

    public static String renderResponseFromEnv(SparkTemplateEngine env, Request request) {
        Map<String, Object> model = new HashMap<>();
        String name = request.queryParams("name");
        if (name != null) {
            model.put("name", name);
        }
        return env.render(new ModelAndView(model, "template.ftl"));
    }

    public static Route home(SparkTemplateEngine env) {
        return (Request request, Response response) -> renderResponseFromEnv(env, request);
    }

    public static void main(String[] args) {
        Spark.port(4567);
        Spark.staticFiles.location("/public");
        SparkTemplateEngine engine = new SparkTemplateEngine();
        Spark.get("/", home(engine));
    }
}

import spark.ModelAndView;
import spark.template.freemarker.FreeMarkerEngine;

class SparkTemplateEngine extends FreeMarkerEngine {
    public SparkTemplateEngine() {
        super();
        configure();
    }

    private void configure() {
        // Configuration settings for FreeMarker can be added here
    }
}