import spark.Request;
import spark.Response;
import spark.Route;
import spark.Spark;

public class HelloWorld {
    public static void main(String[] args) {
        Spark.get("/hello/:username", (request, response) -> renderHello(request.params(":username")));
    }

    private static String renderHello(String username) {
        return "<html><body><h1>Hello, " + username + "!</h1></body></html>";
    }
}
