import java.util.HashMap;
import java.util.Map;

public class WebApp {

    public static void main(String[] args) {
        bind("/hello/<username>", "GET", WebApp::hello);
    }

    private static String renderTemplate(String templateName, Map<String, Object> context) {
        StringBuilder sb = new StringBuilder();
        try {
            // Simulate reading from a file
            if ("hello.html".equals(templateName)) {
                sb.append("Hello, ");
                sb.append(context.get("username"));
                sb.append("!");
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
        return sb.toString();
    }

    private static void bind(String urlPattern, String method, RouteHandler handler) {
        // Simulate URL routing
        System.out.println("Binding " + method + " " + urlPattern + " to handler");
    }

    public static String hello(Map<String, String> params) {
        Map<String, Object> context = new HashMap<>();
        context.put("username", params.get("username"));
        return renderTemplate("hello.html", context);
    }

    @FunctionalInterface
    interface RouteHandler {
        String handle(Map<String, String> params);
    }
}