import spark.Request;
import spark.Response;
import spark.Route;
import spark.Spark;

import java.util.HashMap;
import java.util.Map;

public class Main {
    public static void main(String[] args) {
        Spark.get("/", new Route() {
            @Override
            public Object handle(Request request, Response response) throws Exception {
                return home(request, response);
            }
        });
    }

    public static String render_response_from_env(Map<String, String> env, Request request) {
        String name = request.queryParams("name");
        Map<String, Object> model = new HashMap<>();
        model.put("name", name != null ? name : "World");

        // Simulate template rendering
        return "<html><body>Hello, " + model.get("name") + "!</body></html>";
    }

    public static String home(Request request, Response response) {
        Map<String, String> env = new HashMap<>();
        // Add environment variables if necessary
        return render_response_from_env(env, request);
    }
}