import spark.Request;
import spark.Response;
import spark.Route;
import spark.Spark;

public class HelloWorldApp {

    public static void main(String[] args) {
        Spark.get("/hello/:username", (request, response) -> hello(request, response));
    }

    private static String hello(Request request, Response response) {
        String username = request.params(":username");
        return renderHelloTemplate(username);
    }

    private static String renderHelloTemplate(String username) {
        StringBuilder templateContent = new StringBuilder();
        templateContent.append("<html>")
                .append("<head><title>Hello Page</title></head>")
                .append("<body>")
                .append("<h1>Hello, ").append(username).append("!</h1>")
                .append("</body>")
                .append("</html>");
        return templateContent.toString();
    }
}