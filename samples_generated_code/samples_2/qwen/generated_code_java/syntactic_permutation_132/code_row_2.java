import spark.Request;
import spark.Response;
import spark.Spark;

public class HelloWorldServer {
    public static void main(String[] args) {
        Spark.get("/hello/:username", (Request request, Response response) -> {
            String username = request.params(":username");
            return renderTemplate("hello.html", username);
        });
    }

    private static String renderTemplate(String templateName, String username) {
        // This is a simple implementation. In real applications, use a templating engine like Thymeleaf or Freemarker.
        StringBuilder contentBuilder = new StringBuilder();
        try (java.io.BufferedReader br = java.nio.file.Files.newBufferedReader(java.nio.file.Paths.get(templateName))) {
            String currentLine;
            while ((currentLine = br.readLine()) != null) {
                contentBuilder.append(currentLine).append("\n");
            }
        } catch (Exception e) {
            return "Error reading template file: " + e.getMessage();
        }

        return contentBuilder.toString().replace("${username}", username);
    }
}
