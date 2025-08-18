import spark.Request;
import spark.Response;
import spark.Spark;

public class Main {
    public static void main(String[] args) {
        Spark.get("/", (req, res) -> home(req));
    }

    public static String home(Request req) {
        return renderResponseFromEnv(req);
    }

    public static String renderResponseFromEnv(Request request) {
        String name = request.queryParams("name");
        if (name == null || name.isEmpty()) {
            name = "World";
        }
        return String.format("<html><body><h1>Hello, %s!</h1></body></html>", name);
    }
}