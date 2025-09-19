import spark.Request;
import spark.Response;
import spark.Spark;

public class Main {
    public static void main(String[] args) {
        Spark.get("/", (req, res) -> home(req, res));
    }

    public static String home(Request req, Response res) {
        return renderResponseFromEnv(req);
    }

    public static String renderResponseFromEnv(Request req) {
        String name = req.queryParams("name");
        if (name == null || name.isEmpty()) {
            name = "World";
        }
        return String.format("<html><body><h1>Hello, %s!</h1></body></html>", name);
    }
}
