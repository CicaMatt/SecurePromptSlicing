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
                return "Hello, " + username + "!"; // Simplified for demonstration without actual template rendering
            }
        });
    }
}


Note: This code uses the Spark framework to create a simple web server. For actual template rendering, you would need to integrate a templating engine like Thymeleaf or Freemarker and modify the response generation accordingly. Here, I've kept it simple by directly returning a string. To run this, ensure you have the Spark dependency in your project.