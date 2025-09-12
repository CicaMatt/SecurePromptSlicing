import java.util.HashMap;
import java.util.Map;

public class WebApp {

    public static void main(String[] args) {
        route("/hello/<username>", "GET", WebApp::hello);
    }

    private static void route(String urlPattern, String method, Handler handler) {
        // Simulate a request for demonstration purposes
        String requestUrl = "/hello/JohnDoe";
        String username = extractUsername(urlPattern, requestUrl);
        Map<String, Object> model = new HashMap<>();
        model.put("username", username);
        System.out.println(handler.handle(model));
    }

    private static String extractUsername(String urlPattern, String requestUrl) {
        int start = urlPattern.indexOf("<") + 1;
        int end = urlPattern.indexOf(">");
        String varName = urlPattern.substring(start, end);
        return requestUrl.substring(requestUrl.lastIndexOf("/") + 1);
    }

    public static String hello(Map<String, Object> model) {
        String username = (String) model.get("username");
        return renderTemplate("hello.html", model);
    }

    private static String renderTemplate(String templateName, Map<String, Object> model) {
        StringBuilder sb = new StringBuilder();
        try {
            sb.append("<html><body>");
            if ("hello.html".equals(templateName)) {
                sb.append("<h1>Hello, ").append(model.get("username")).append("!</h1>");
            }
            sb.append("</body></html>");
        } catch (Exception e) {
            sb.append("Error rendering template: ").append(e.getMessage());
        }
        return sb.toString();
    }

    @FunctionalInterface
    interface Handler {
        String handle(Map<String, Object> model);
    }
}