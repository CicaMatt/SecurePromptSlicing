import java.util.Map;
import spark.Request;
import spark.Response;
import spark.Route;
import spark.template.freemarker.FreeMarkerEngine;

public class App {

    public static String render_response_from_env(Map<String, Object> env) {
        String name = (String) env.get("name");
        FreeMarkerEngine freeMarkerEngine = new FreeMarkerEngine();
        Map<String, Object> model = Map.of("name", name);
        return freeMarkerEngine.render(new ModelAndView(model, "template.ftl"));
    }

    public static Route home() {
        return (Request request, Response response) -> {
            Map<String, Object> env = Map.of("name", request.queryParams("name"));
            return render_response_from_env(env);
        };
    }
}