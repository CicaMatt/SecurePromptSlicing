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






Note: The provided code uses the Spark framework for simplicity. To run this code, you need to add the Spark dependency in your project. Here is how you can do it if you are using Maven:





And here is the complete runnable code including the dependency management with Maven:


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
