import spark.Request;
import spark.Response;
import spark.Route;
import spark.Spark;
import java.util.HashMap;
import java.util.Map;

public class HelloWorldDecorator {

    public static void main(String[] args) {
        Spark.get("/hello/:username", (request, response) -> hello(request, response));
    }

    private static String hello(Request request, Response response) {
        String username = request.params(":username");
        Map<String, Object> model = new HashMap<>();
        model.put("username", username);
        return renderTemplate(model);
    }

    private static String renderTemplate(Map<String, Object> model) {
        // Simulating a template engine to load hello.html and replace {{username}} with the actual value
        String template = "<html><body><h1>Hello, {{username}}!</h1></body></html>";
        return template.replace("{{username}}", (String) model.get("username"));
    }
}
