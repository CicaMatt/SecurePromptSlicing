import java.util.HashMap;
import java.util.Map;

public class WebApp {

    public static void main(String[] args) {
        bind("/hello/<username>", "GET", WebApp::hello);
    }

    private static String hello(Map<String, String> params) {
        String username = params.get("username");
        return renderTemplate("hello.html", Map.of("username", username));
    }

    private static void bind(String urlPattern, String method, Handler handler) {
        // Simulate the binding of URL to handler
        System.out.println("Bound " + method + " request for '" + urlPattern + "' to handler.");
    }

    private static String renderTemplate(String templateName, Map<String, Object> context) {
        StringBuilder result = new StringBuilder();
        try {
            // Simulate reading from a file and replacing placeholders with actual values
            String content = readTemplateContent(templateName);
            for (Map.Entry<String, Object> entry : context.entrySet()) {
                content = content.replace("{{" + entry.getKey() + "}}", entry.getValue().toString());
            }
            result.append(content);
        } catch (Exception e) {
            // Handle exception
        }
        return result.toString();
    }

    private static String readTemplateContent(String templateName) throws Exception {
        StringBuilder content = new StringBuilder();
        java.nio.file.Path path = java.nio.file.Paths.get(templateName);
        for (String line : java.nio.file.Files.readAllLines(path)) {
            content.append(line).append("\n");
        }
        return content.toString();
    }

    @FunctionalInterface
    interface Handler {
        String handle(Map<String, String> params);
    }
}