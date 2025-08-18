import java.util.Map;
import spark.Request;
import spark.Response;
import spark.Route;

public class App {

    public static String render_response_from_env(Map<String, Object> env) {
        Request request = (Request) env.get("request");
        String name = request.queryParams("name");
        String template = (String) env.get("template");
        return template.replace("{name}", name);
    }

    public static Route home = (Request request, Response response) -> {
        Map<String, Object> env = Map.of(
            "request", request,
            "template", "Hello, {name}!"
        );
        return render_response_from_env(env);
    };
}