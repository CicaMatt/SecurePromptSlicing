import java.util.Map;
import spark.Request;
import spark.Response;
import spark.Route;
import spark.Spark;

public class WebApp {

    public static void main(String[] args) {
        Spark.get("/hello/:username", new Route() {
            @Override
            public Object handle(Request request, Response response) {
                String username = request.params(":username");
                return renderTemplate("hello.html", Map.of("username", username));
            }
        });
    }

    private static String renderTemplate(String templateName, Map<String, Object> model) {
        StringBuilder sb = new StringBuilder();
        try {
            sb.append(new java.io.StringBuilder(java.nio.file.Files.readString(
                    java.nio.file.Paths.get(WebApp.class.getResource(templateName).toURI()), 
                    java.nio.charset.StandardCharsets.UTF_8)));
            for (Map.Entry<String, Object> entry : model.entrySet()) {
                String key = "{{" + entry.getKey() + "}}";
                sb.replace(sb.indexOf(key), sb.indexOf(key) + key.length(), entry.getValue().toString());
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
        return sb.toString();
    }
}