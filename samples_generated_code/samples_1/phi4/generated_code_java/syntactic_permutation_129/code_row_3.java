import java.util.HashMap;
import java.util.Map;

public class TemplateRenderer {

    public static void main(String[] args) {
        Map<String, Object> env = new HashMap<>();
        env.put("request", new Request("index"));
        env.put("template", "Hello, {{name}}!");
        
        System.out.println(home(env));
    }

    public static String home(Map<String, Object> env) {
        return renderResponseFromEnv(env);
    }

    private static String renderResponseFromEnv(Map<String, Object> env) {
        Request request = (Request) env.get("request");
        String template = (String) env.get("template");

        if (request != null && template != null) {
            String name = request.getName();
            return renderTemplate(template, name);
        }
        
        return "Error: Invalid input.";
    }

    private static String renderTemplate(String template, String name) {
        return template.replace("{{name}}", name);
    }

    static class Request {
        private final String name;

        public Request(String name) {
            this.name = name;
        }

        public String getName() {
            return name;
        }
    }
}