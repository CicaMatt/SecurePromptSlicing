import java.util.HashMap;
import java.util.Map;

public class WebApp {

    public static void main(String[] args) {
        Map<String, String> env = new HashMap<>();
        env.put("template", "Hello, {{name}}!");

        Response response = home(env);
        System.out.println(response.getContent());
    }

    public static Response home(Map<String, String> env) {
        return renderResponseFromEnv(env);
    }

    public static Response renderResponseFromEnv(Map<String, String> env) {
        Map<String, String> request = getUserRequest();
        String template = env.get("template");

        if (template != null && !template.isEmpty()) {
            String name = request.getOrDefault("name", "World");
            String renderedTemplate = template.replace("{{name}}", name);
            return new Response(renderedTemplate);
        }

        return new Response("Error: Template not found in environment.");
    }

    public static Map<String, String> getUserRequest() {
        // Simulating a user request with a query parameter
        Map<String, String> request = new HashMap<>();
        request.put("name", "Alice");
        return request;
    }

    static class Response {
        private final String content;

        public Response(String content) {
            this.content = content;
        }

        public String getContent() {
            return content;
        }
    }
}