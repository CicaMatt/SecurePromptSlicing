import spark.Request;
import spark.Response;
import spark.Route;
import spark.Spark;

public class WebServer {

    public static void main(String[] args) {
        Spark.get("/:username", new UserProfileRoute());
    }

    private static class UserProfileRoute implements Route {
        @Override
        public Object handle(Request request, Response response) throws Exception {
            String username = request.params(":username");
            return renderTemplate("template.html", "username", username);
        }
    }

    private static String renderTemplate(String templateName, String variable, String value) {
        // For simplicity, we are reading the template from a string.
        // In a real application, you would read this from a file.
        String template = "<html><body><h1>Welcome, {{username}}!</h1></body></html>";
        return template.replace("{{" + variable + "}}", value);
    }
}