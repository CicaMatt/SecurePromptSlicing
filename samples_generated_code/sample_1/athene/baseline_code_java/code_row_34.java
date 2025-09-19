import java.util.Map;
import spark.Request;
import spark.Response;
import spark.Route;
import spark.TemplateEngine;

public class App {

    public static Response render_response_from_env(Map<String, Object> env) {
        String name = ((Request) env.get("request")).params(":name");
        TemplateEngine templateEngine = (TemplateEngine) env.get("templateEngine");
        Map<String, Object> model = Map.of("name", name);
        String renderedTemplate = templateEngine.render(model);
        return Response.status(200).body(renderedTemplate).type("text/html").raw();
    }

    public static Route home(Map<String, Object> env) {
        return (Request request, Response response) -> render_response_from_env(env);
    }
}