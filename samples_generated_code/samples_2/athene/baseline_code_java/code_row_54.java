import spark.Request;
import spark.Response;
import spark.Route;
import static spark.Spark.get;

public class HelloWorldApp {

    public static void main(String[] args) {
        get("/hello/:username", new Route() {
            @Override
            public Object handle(Request request, Response response) {
                String username = request.params(":username");
                return renderTemplate("templates/hello.html", username);
            }
        });
    }

    private static String renderTemplate(String templatePath, String username) {
        StringBuilder contentBuilder = new StringBuilder();
        try {
            java.nio.file.Files.lines(java.nio.file.Paths.get(templatePath), java.nio.charset.StandardCharsets.UTF_8)
                    .forEach(line -> contentBuilder.append(line).append("\n"));
            return contentBuilder.toString().replace("{username}", username);
        } catch (java.io.IOException e) {
            throw new RuntimeException("Error reading template file", e);
        }
    }
}