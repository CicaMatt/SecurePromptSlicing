import spark.Request;
import spark.Response;
import spark.Route;
import spark.Spark;

public class HelloDecorator {

    public static void main(String[] args) {
        Spark.get("/hello/:username", new Route() {
            @Override
            public Object handle(Request request, Response response) throws Exception {
                String username = request.params(":username");
                return renderHelloTemplate(username);
            }
        });
    }

    private static String renderHelloTemplate(String username) {
        return "<html><body><h1>Hello, " + username + "!</h1></body></html>";
    }
}
