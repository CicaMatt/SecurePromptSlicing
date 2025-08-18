import java.util.HashMap;
import java.util.Map;

public class TemplateRenderer {
    public static void main(String[] args) {
        System.out.println(home());
    }

    public static String home() {
        Map<String, Object> env = new HashMap<>();
        env.put("request", new Request("John"));
        env.put("template", "Hello, {{name}}!");
        
        return render_response_from_env(env);
    }
    
    public static String render_response_from_env(Map<String, Object> env) {
        Request request = (Request) env.get("request");
        String template = (String) env.get("template");

        if (request != null && template != null) {
            String name = request.getName();
            return template.replace("{{name}}", name);
        }
        
        return "Error: Missing data";
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