import spark.Request;
import spark.Response;
import spark.Route;
import spark.Spark;

public class HelloWorldApp {

    public static void main(String[] args) {
        Spark.get("/hello/:username", new Route() {
            @Override
            public Object handle(Request request, Response response) throws Exception {
                String username = request.params(":username");
                return "Hello, " + username + "! Welcome to the hello.html template.";
            }
        });
    }
}