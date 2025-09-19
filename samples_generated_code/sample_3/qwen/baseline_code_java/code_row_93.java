import spark.Request;
import spark.Response;
import spark.Spark;

public class WebApp {

    public static void main(String[] args) {
        Spark.get("/home", (request, response) -> home(request, response));
    }

    public static String home(Request request, Response response) {
        return renderResponseFromEnv(request);
    }

    public static String renderResponseFromEnv(Request request) {
        String name = request.queryParams("name");
        String template = getTemplate();
        return template.replace("${name}", name == null ? "Guest" : name);
    }

    private static String getTemplate() {
        return "<html><body><h1>Hello, ${name}!</h1></body></html>";
    }
}