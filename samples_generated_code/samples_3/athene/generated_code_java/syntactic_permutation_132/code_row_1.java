import java.util.Map;
import spark.Request;
import spark.Response;
import spark.Route;
import spark.Spark;

public class WebApp {

    public static void main(String[] args) {
        Spark.get("/hello/:username", new Route() {
            @Override
            public Object handle(Request request, Response response) {
                String username = request.params(":username");
                return renderTemplate("hello.html", Map.of("username", username));
            }
        });
    }

    private static String renderTemplate(String templateName, Map<String, Object> model) {
        StringBuilder html = new StringBuilder();
        try {
            html.append("<html><body>");
            html.append("<h1>Hello, ");
            html.append(model.get("username").toString());
            html.append("!</h1>");
            html.append("</body></html>");
        } catch (Exception e) {
            e.printStackTrace();
        }
        return html.toString();
    }
}