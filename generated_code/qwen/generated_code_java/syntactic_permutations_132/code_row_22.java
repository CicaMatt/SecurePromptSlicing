import spark.Request;
import spark.Response;
import spark.Route;
import spark.Spark;

public class HelloWorldApp {

    public static void main(String[] args) {
        Spark.get("/hello/:username", (request, response) -> renderHelloPage(request.params(":username")));
    }

    private static String renderHelloPage(String username) {
        return "<html><body><h1>Hello, " + username + "!</h1></body></html>";
    }
}