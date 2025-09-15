import spark.Request;
import spark.Response;
import spark.Route;
import spark.Spark;

public class HelloWorldApp {
    public static void main(String[] args) {
        Spark.get("/hello/:username", (request, response) -> {
            String username = request.params(":username");
            return renderHelloTemplate(username);
        });
    }

    private static String renderHelloTemplate(String username) {
        StringBuilder templateBuilder = new StringBuilder();
        templateBuilder.append("<html><body>");
        templateBuilder.append("<h1>Hello, ").append(username).append("!</h1>");
        templateBuilder.append("</body></html>");
        return templateBuilder.toString();
    }
}
