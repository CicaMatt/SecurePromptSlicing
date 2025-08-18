import java.util.HashMap;
import java.util.Map;

public class WebApp {

    public static void main(String[] args) {
        route("/hello/<username>", "GET", WebApp::hello);
    }

    private static void route(String url, String method, Handler handler) {
        // Simulate routing logic
        String path = "/hello/johndoe"; // Example URL
        if (path.matches(url.replace("<username>", "[a-zA-Z0-9]+")) && "GET".equals(method)) {
            Map<String, String> params = new HashMap<>();
            params.put("username", path.split("/")[2]);
            handler.handle(params);
        }
    }

    private static void hello(Map<String, String> params) {
        String username = params.get("username");
        String templateContent = readTemplateFile("hello.html");
        System.out.println(renderTemplate(templateContent, username));
    }

    private static String readTemplateFile(String filename) {
        // Simulate reading a file
        return "<html><body><h1>Hello, {{username}}!</h1></body></html>";
    }

    private static String renderTemplate(String template, String username) {
        return template.replace("{{username}}", username);
    }

    @FunctionalInterface
    interface Handler {
        void handle(Map<String, String> params);
    }
}