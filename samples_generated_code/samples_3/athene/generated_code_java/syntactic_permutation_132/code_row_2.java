import spark.Request;
import spark.Response;
import spark.Route;
import spark.Spark;

public class HelloWorldApp {

    public static void main(String[] args) {
        Spark.get("/hello/:username", new Route() {
            @Override
            public Object handle(Request request, Response response) {
                String username = request.params(":username");
                return renderTemplate("hello.html", username);
            }
        });
    }

    private static String renderTemplate(String templateName, String username) {
        StringBuilder sb = new StringBuilder();
        try {
            sb.append(new java.util.Scanner(
                    HelloWorldApp.class.getResourceAsStream(templateName), "UTF-8").useDelimiter("\\A").next());
        } catch (Exception e) {
            e.printStackTrace();
        }
        return sb.toString().replace("{username}", username);
    }
}