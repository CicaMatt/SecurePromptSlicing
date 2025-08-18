import spark.Request;
import spark.Response;
import spark.Spark;

public class Main {
    public static void main(String[] args) {
        Spark.get("/", (request, response) -> home(request, response));
    }

    public static String home(Request request, Response response) {
        return renderResponseFromEnv(request, System.getenv());
    }

    public static String renderResponseFromEnv(Request request, java.util.Map<String, String> env) {
        String name = request.queryParams("name");
        String template = env.getOrDefault("TEMPLATE", "Hello, %s!");
        return String.format(template, name != null ? name : "World");
    }
}