import spark.Request;
import spark.Response;
import spark.Route;
import spark.Spark;

public class Main {
    public static void main(String[] args) {
        Spark.get("/", (request, response) -> home(request, response));
    }

    public static String home(Request request, Response response) {
        return renderResponseFromEnv(request);
    }

    public static String renderResponseFromEnv(Request request) {
        String name = request.queryParams("name");
        String template = getTemplate();
        return template.replace("{name}", name != null ? name : "Guest");
    }

    private static String getTemplate() {
        return "<html><body><h1>Hello, {name}!</h1></body></html>";
    }
}