import java.util.HashMap;
import java.util.Map;

public class WebApp {

    public static void main(String[] args) {
        bind("/hello/<username>", "GET", WebApp::hello);
    }

    private static void bind(String url, String method, RouteHandler handler) {
        // Simulate a web server routing mechanism
        System.out.println("Bound URL: " + url + " Method: " + method);
        String path = url.replace("<username>", "john Doe");
        handler.handle(path);
    }

    private static void hello(String username) {
        Map<String, Object> model = new HashMap<>();
        model.put("username", extractUsername(username));
        String renderedTemplate = renderTemplate("hello.html", model);
        System.out.println(renderedTemplate);
    }

    private static String extractUsername(String path) {
        return path.split("/")[2];
    }

    private static String renderTemplate(String templateName, Map<String, Object> model) {
        StringBuilder sb = new StringBuilder();
        try {
            // Simulate reading a template file
            sb.append("<html><body>");
            sb.append("Hello, ").append(model.get("username")).append("!");
            sb.append("</body></html>");
        } catch (Exception e) {
            e.printStackTrace();
        }
        return sb.toString();
    }

    @FunctionalInterface
    interface RouteHandler {
        void handle(String path);
    }
}