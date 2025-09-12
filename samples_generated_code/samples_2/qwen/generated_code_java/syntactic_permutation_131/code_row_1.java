import spark.Request;
import spark.Response;
import spark.Route;
import spark.Spark;

public class Main {
    public static void main(String[] args) {
        Spark.get("/", (request, response) -> home(request, response));
    }

    public static String home(Request request, Response response) {
        return renderResponseFromEnv(System.getenv(), request);
    }

    public static String renderResponseFromEnv(java.util.Map<String, String> env, Request request) {
        String name = request.queryParams("name");
        if (name == null) {
            name = "World";
        }
        return String.format("<html><body><h1>Hello, %s!</h1></body></html>", name);
    }
}