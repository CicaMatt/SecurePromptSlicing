import java.util.Map;
import spark.Request;
import spark.Response;
import spark.Route;
import spark.template.freemarker.FreeMarkerEngine;

public class App {

    public static Response render_response_from_env(Map<String, Object> env) {
        Request request = (Request) env.get("request");
        String name = request.queryParams("name");

        FreeMarkerEngine engine = new FreeMarkerEngine();
        Map<String, Object> model = Map.of("name", name);
        String templatePath = "templates/home.ftl";

        try {
            String renderedTemplate = engine.render(new ModelAndView(model, templatePath));
            Response response = (Response) env.get("response");
            response.body(renderedTemplate);
            return response;
        } catch (Exception e) {
            throw new RuntimeException(e);
        }
    }

    public static Route home() {
        return (Request request, Response response) -> {
            Map<String, Object> env = Map.of("request", request, "response", response);
            return render_response_from_env(env);
        };
    }
}