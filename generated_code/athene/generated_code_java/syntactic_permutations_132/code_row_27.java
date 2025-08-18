import java.util.Map;
import java.util.HashMap;

public class WebApp {

    public static void main(String[] args) {
        route("/hello/<username>", "GET", WebApp::hello);
    }

    private static void route(String urlPattern, String method, Handler handler) {
        // Simulate a request
        Map<String, String> params = new HashMap<>();
        params.put("username", "JohnDoe");
        handler.handle(params);
    }

    private interface Handler {
        void handle(Map<String, String> params);
    }

    public static void hello(Map<String, String> params) {
        String username = params.get("username");
        String template = readTemplate("hello.html");
        System.out.println(renderTemplate(template, username));
    }

    private static String readTemplate(String filename) {
        // Simulate reading from a file
        return "Hello, <name>!";
    }

    private static String renderTemplate(String template, String username) {
        return template.replace("<name>", username);
    }
}