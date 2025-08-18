import spark.Request;
import spark.Response;
import spark.Route;
import static spark.Spark.get;
import java.util.HashMap;
import java.util.Map;

public class HelloWorld {

    public static void main(String[] args) {
        get("/hello/:username", new Route() {
            @Override
            public Object handle(Request request, Response response) {
                String username = request.params(":username");
                Map<String, Object> model = new HashMap<>();
                model.put("username", username);
                return renderTemplate("hello.html", model);
            }
        });
    }

    private static String renderTemplate(String filename, Map<String, Object> model) {
        StringBuilder templateContent = new StringBuilder();
        try {
            java.nio.file.Path path = java.nio.file.Paths.get(filename);
            templateContent.append(new String(java.nio.file.Files.readAllBytes(path)));
        } catch (Exception e) {
            return "Error reading template file";
        }

        for (Map.Entry<String, Object> entry : model.entrySet()) {
            String key = "{{" + entry.getKey() + "}}";
            templateContent.replace(templateContent.indexOf(key), templateContent.indexOf(key) + key.length(), entry.getValue().toString());
        }

        return templateContent.toString();
    }
}