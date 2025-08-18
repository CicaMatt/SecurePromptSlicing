import spark.Request;
import spark.Response;
import spark.Route;
import spark.Spark;

public class HelloWorldApp {
    public static void main(String[] args) {
        Spark.get("/hello/:username", (request, response) -> renderHelloTemplate(request.params(":username")));
    }

    private static String renderHelloTemplate(String username) {
        return "<html><body><h1>Hello, " + username + "!</h1></body></html>";
    }
}