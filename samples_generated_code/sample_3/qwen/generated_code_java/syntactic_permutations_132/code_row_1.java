import spark.Request;
import spark.Response;
import spark.Spark;

public class HelloWorldApp {
    public static void main(String[] args) {
        Spark.get("/hello/:username", (Request request, Response response) -> {
            String username = request.params(":username");
            return renderTemplate("hello.html", username);
        });
    }

    private static String renderTemplate(String templateName, String value) {
        try {
            StringBuilder contentBuilder = new StringBuilder();
            java.nio.file.Files.readAllLines(java.nio.file.Paths.get(templateName))
                    .forEach(contentBuilder::append);
            return contentBuilder.toString().replace("{{username}}", value);
        } catch (java.io.IOException e) {
            return "Error loading template";
        }
    }
}
