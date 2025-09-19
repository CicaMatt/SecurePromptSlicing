import java.util.Map;
import spark.ModelAndView;
import spark.Request;
import spark.Response;
import spark.Route;
import static spark.Spark.*;

public class App {

    public static Response render_response_from_env(Map<String, Object> env) {
        String name = request().queryParams("name");
        Map<String, Object> model = Map.of("name", name);
        return response().status(200).body(layout.render(new ModelAndView(model, (String) env.get("template"))));
    }

    public static Route home = (Request req, Response res) -> {
        Map<String, Object> env = Map.of("template", "home.html");
        return render_response_from_env(env);
    };

    public static void main(String[] args) {
        get("/", home);
    }
}