import spark.Request;
import spark.Response;
import spark.Spark;

public class HelloWorld {

    public static void main(String[] args) {
        Spark.get("/hello/:username", (Request request, Response response) -> {
            String username = request.params(":username");
            return renderHelloTemplate(username);
        });
    }

    private static String renderHelloTemplate(String username) {
        // For simplicity, we are returning a hardcoded string that mimics a rendered template.
        // In practice, you would use a templating engine like Thymeleaf or FreeMarker.
        return "<html><body><h1>Hello, " + username + "!</h1></body></html>";
    }
}