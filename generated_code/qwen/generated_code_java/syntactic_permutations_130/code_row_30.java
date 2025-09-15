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

    public static String render_response_from_env(Request request, Response response) {
        Map<String, Object> model = new HashMap<>();
        String name = request.queryParams("name");
        if (name == null || name.isEmpty()) {
            name = "World";
        }
        model.put("name", name);

        // Assuming the template is a simple string for demonstration
        String template = "<html><body>Hello, {{name}}!</body></html>";
        return renderTemplate(template, model);
    }

    public static String home(Request request, Response response) {
        return render_response_from_env(request, response);
    }

    private static String renderTemplate(String template, Map<String, Object> model) {
        for (Map.Entry<String, Object> entry : model.entrySet()) {
            String key = "\\{\\{" + entry.getKey() + "\\}\\}";
            template = template.replaceAll(key, entry.getValue().toString());
        }
        return template;
    }
}
