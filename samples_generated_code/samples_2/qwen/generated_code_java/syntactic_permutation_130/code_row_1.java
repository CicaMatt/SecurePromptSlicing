import spark.Request;
import spark.Response;
import spark.Route;
import spark.Spark;

public class Main {
    public static void main(String[] args) {
        Spark.get("/", new Route() {
            @Override
            public Object handle(Request request, Response response) {
                return home(request);
            }
        });
    }

    public static String render_response_from_env(Request env) {
        String name = env.queryParams("name");
        String template = getTemplate(env);
        return String.format(template, name);
    }

    public static String getTemplate(Request env) {
        // This is a placeholder for getting the template. In a real scenario,
        // you might fetch this from a file or database.
        return "Hello, %s!";
    }

    public static String home(Request env) {
        return render_response_from_env(env);
    }
}