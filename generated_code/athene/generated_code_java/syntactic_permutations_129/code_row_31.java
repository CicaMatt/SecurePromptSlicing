import java.util.Map;
import spark.Request;
import spark.Response;
import spark.Route;
import spark.template.freemarker.FreeMarkerEngine;

public class App {

    public static String render_response_from_env(Map<String, Object> env) {
        Request request = (Request) env.get("request");
        String name = request.params(":name");

        FreeMarkerEngine engine = (FreeMarkerEngine) env.get("freeMarkerEngine");
        String templatePath = "templates/home.ftl";

        Map<String, Object> attributes = new java.util.HashMap<>();
        attributes.put("name", name);

        return engine.render(new freemarker.template.TemplateHashModel(attributes), templatePath);
    }

    public static Route home(final FreeMarkerEngine freeMarkerEngine) {
        return (Request request, Response response) -> {
            Map<String, Object> env = new java.util.HashMap<>();
            env.put("request", request);
            env.put("freeMarkerEngine", freeMarkerEngine);
            return render_response_from_env(env);
        };
    }
}