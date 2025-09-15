import spark.Request;
import spark.Response;
import spark.Route;
import spark.Spark;

public class UsernameDecorator {

    public static void main(String[] args) {
        Spark.get("/:username", new Route() {
            @Override
            public Object handle(Request request, Response response) {
                String username = request.params(":username");
                return renderTemplate(username);
            }
        });
    }

    private static String renderTemplate(String username) {
        // Simulating a template rendering process
        StringBuilder htmlContent = new StringBuilder();
        htmlContent.append("<html>")
                   .append("<body>")
                   .append("<h1>Welcome, ").append(username).append("!</h1>")
                   .append("</body>")
                   .append("</html>");
        return htmlContent.toString();
    }
}
