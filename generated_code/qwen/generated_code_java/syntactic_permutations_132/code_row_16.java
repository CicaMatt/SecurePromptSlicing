import spark.Request;
import spark.Response;
import spark.Route;
import spark.Spark;

public class HelloWorldApp {

    public static void main(String[] args) {
        Spark.get("/hello/:username", new Route() {
            @Override
            public Object handle(Request request, Response response) {
                String username = request.params(":username");
                return renderHelloTemplate(username);
            }
        });
    }

    private static String renderHelloTemplate(String username) {
        // This is a simple template rendering. In a real application, you might use a templating engine like Thymeleaf or Freemarker.
        return "<html><body><h1>Hello, " + username + "!</h1></body></html>";
    }
}
