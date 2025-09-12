import java.util.Map;
import spark.ModelAndView;
import spark.Request;
import spark.Response;
import spark.Route;
import spark.template.freemarker.FreeMarkerEngine;

public class App {

    public static Response render_response_from_env(Map<String, Object> env) {
        String name = Request.params(":name");
        ModelAndView modelAndView = new ModelAndView(env, "template.ftl");
        FreeMarkerEngine freeMarkerEngine = new FreeMarkerEngine();
        String renderedTemplate = freeMarkerEngine.render(modelAndView);
        Response response = Response.status(200).body(renderedTemplate);
        return response;
    }

    public static Route home(final Map<String, Object> env) {
        return (Request request, Response response) -> {
            Map<String, Object> model = Map.of("name", request.params(":name"));
            env.putAll(model);
            return render_response_from_env(env).body();
        };
    }
}