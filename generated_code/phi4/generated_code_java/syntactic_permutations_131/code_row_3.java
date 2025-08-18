import java.io.IOException;
import java.util.HashMap;
import java.util.Map;

public class WebApp {

    public static void main(String[] args) {
        Map<String, String> env = new HashMap<>();
        env.put("template", "Hello, {{name}}!");
        
        try {
            System.out.println(home(env));
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static String renderResponseFromEnv(Map<String, String> env) throws IOException {
        String template = env.getOrDefault("template", "No template found");
        String name = getRequestParam("name");
        
        String renderedTemplate = template.replace("{{name}}", name);
        return createResponse(renderedTemplate);
    }

    public static String home(Map<String, String> env) throws IOException {
        return renderResponseFromEnv(env);
    }

    private static String getRequestParam(String paramName) {
        // Simulate getting a parameter from the request
        // In a real scenario, this would be replaced with actual request handling logic
        if (paramName.equals("name")) {
            return "World";
        }
        return "";
    }

    private static String createResponse(String content) throws IOException {
        // Simulate creating an HTTP response
        return "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\n" + content;
    }
}