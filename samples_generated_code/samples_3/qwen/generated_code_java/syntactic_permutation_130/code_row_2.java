import spark.Request;
import spark.Response;
import spark.Route;
import spark.Spark;

public class Main {
    public static void main(String[] args) {
        Spark.get("/", new Route() {
            @Override
            public Object handle(Request request, Response response) throws Exception {
                return home(request, response);
            }
        });
    }

    public static String render_response_from_env(Request request, Response response) {
        String name = request.queryParams("name");
        String template = getTemplate();
        return String.format(template, name);
    }

    private static String getTemplate() {
        return "Hello, %s!";
    }

    public static String home(Request request, Response response) {
        return render_response_from_env(request, response);
    }
}