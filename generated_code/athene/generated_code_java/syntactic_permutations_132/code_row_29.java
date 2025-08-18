import java.util.Map;
import java.util.HashMap;
import spark.Route;
import spark.Request;
import spark.Response;
import static spark.Spark.get;
import spark.template.freemarker.FreeMarkerEngine;

public class App {
    private static final FreeMarkerEngine freeMarker = new FreeMarkerEngine();

    public static void main(String[] args) {
        get("/hello/:username", helloRoute());
    }

    private static Route helloRoute() {
        return (Request req, Response res) -> {
            String username = req.params(":username");
            Map<String, Object> attributes = new HashMap<>();
            attributes.put("username", username);
            return freeMarker.render(attributes, "templates/hello.html");
        };
    }
}