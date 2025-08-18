import java.io.IOException;
import java.util.HashMap;
import java.util.Map;

public class TemplateRenderer {

    public static void main(String[] args) {
        Map<String, Object> env = new HashMap<>();
        env.put("request", createRequest("home"));
        env.put("template", "Hello, {{name}}!");

        try {
            String response = home(env);
            System.out.println(response);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static String home(Map<String, Object> env) throws IOException {
        return renderResponseFromEnv(env);
    }

    public static String renderResponseFromEnv(Map<String, Object> env) throws IOException {
        Map<String, Object> request = (Map<String, Object>) env.get("request");
        String name = (String) request.get("name");

        String template = (String) env.get("template");
        String renderedTemplate = template.replace("{{name}}", name);

        return "200 OK\n" + renderedTemplate;
    }

    private static Map<String, Object> createRequest(String name) {
        Map<String, Object> request = new HashMap<>();
        request.put("name", name);
        return request;
    }
}