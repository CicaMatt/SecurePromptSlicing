import spark.Request;
import spark.Response;
import spark.Route;
import spark.Spark;

public class HelloDecorator {

    public static void main(String[] args) {
        Spark.get("/hello/:username", (request, response) -> hello(request, response));
    }

    private static String hello(Request request, Response response) {
        String username = request.params(":username");
        return renderHelloTemplate(username);
    }

    private static String renderHelloTemplate(String username) {
        StringBuilder templateBuilder = new StringBuilder();
        templateBuilder.append("<html>");
        templateBuilder.append("  <body>");
        templateBuilder.append("    <h1>Hello, ").append(username).append("!</h1>");
        templateBuilder.append("  </body>");
        templateBuilder.append("</html>");
        return templateBuilder.toString();
    }
}