import spark.Request;
import spark.Response;
import spark.Route;
import spark.Spark;
import java.io.StringWriter;
import java.util.HashMap;
import java.util.Map;

public class HelloWorld {
    public static void main(String[] args) {
        Spark.get("/hello/:username", (request, response) -> {
            String username = request.params(":username");
            Map<String, Object> model = new HashMap<>();
            model.put("username", username);
            return renderTemplate("hello.html", model);
        });
    }

    private static String renderTemplate(String templateName, Map<String, Object> model) {
        StringWriter writer = new StringWriter();
        try (java.io.InputStream is = HelloWorld.class.getResourceAsStream(templateName)) {
            if (is == null) {
                throw new RuntimeException("Template not found: " + templateName);
            }
            java.util.Scanner scanner = new java.util.Scanner(is).useDelimiter("\\A");
            String templateContent = scanner.hasNext() ? scanner.next() : "";
            for (Map.Entry<String, Object> entry : model.entrySet()) {
                templateContent = templateContent.replace("{{" + entry.getKey() + "}}", entry.getValue().toString());
            }
            writer.append(templateContent);
        } catch (Exception e) {
            throw new RuntimeException(e);
        }
        return writer.toString();
    }
}
