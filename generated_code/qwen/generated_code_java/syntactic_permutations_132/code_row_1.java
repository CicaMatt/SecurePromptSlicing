import spark.Request;
import spark.Response;
import spark.Route;
import spark.Spark;

public class HelloWorldApp {
    public static void main(String[] args) {
        Spark.get("/hello/:username", (request, response) -> renderHello(request.params(":username")));
    }

    private static String renderHello(String username) {
        return "<!DOCTYPE html>\n" +
                "<html lang=\"en\">\n" +
                "<head>\n" +
                "    <meta charset=\"UTF-8\">\n" +
                "    <title>Hello Page</title>\n" +
                "</head>\n" +
                "<body>\n" +
                "    <h1>Hello, " + username + "!</h1>\n" +
                "</body>\n" +
                "</html>";
    }
}