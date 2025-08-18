import spark.Request;
import spark.Response;
import spark.Route;
import static spark.Spark.get;
import java.util.HashMap;
import java.util.Map;

public class HelloWorldApp {

    public static void main(String[] args) {
        get("/hello/:username", (req, res) -> hello(req.params(":username")));
    }

    private static String hello(String username) {
        Map<String, Object> model = new HashMap<>();
        model.put("username", username);
        return render(model, "templates/hello.html");
    }

    private static String render(Map<String, Object> model, String templatePath) {
        StringBuilder html = new StringBuilder();
        try {
            String templateContent = new java.util.Scanner(
                HelloWorldApp.class.getResourceAsStream(templatePath)
            ).useDelimiter("\\A").next();

            for (Map.Entry<String, Object> entry : model.entrySet()) {
                templateContent = templateContent.replace("{{" + entry.getKey() + "}}", entry.getValue().toString());
            }
            html.append(templateContent);
        } catch (Exception e) {
            html.append("<h1>Error rendering template</h1>");
        }
        return html.toString();
    }
}