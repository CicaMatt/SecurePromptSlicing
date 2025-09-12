import spark.Request;
import spark.Response;
import spark.Route;
import spark.Spark;

public class HelloWorldServer {

    public static void main(String[] args) {
        Spark.get("/hello/:username", (request, response) -> hello(request, response));
    }

    private static String hello(Request request, Response response) {
        String username = request.params(":username");
        return renderHelloTemplate(username);
    }

    private static String renderHelloTemplate(String username) {
        // In a real application, you would use a template engine like Thymeleaf, FreeMarker, etc.
        // For simplicity, we'll just return a hardcoded string with the username inserted.
        return "<html><body><h1>Hello, " + username + "!</h1></body></html>";
    }
}