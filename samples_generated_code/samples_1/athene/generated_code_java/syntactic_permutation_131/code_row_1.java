import java.util.HashMap;
import java.util.Map;

public class TemplateRenderer {

    public static class Environment {
        private Map<String, String> templates = new HashMap<>();

        public void setTemplate(String key, String template) {
            templates.put(key, template);
        }

        public String getTemplate(String key) {
            return templates.get(key);
        }
    }

    public static class Request {
        private Map<String, Object> data = new HashMap<>();

        public <T> T getData(String key) {
            return (T) data.get(key);
        }

        public void setData(String key, Object value) {
            data.put(key, value);
        }
    }

    public static String render_response_from_env(Environment env, Request request) {
        String template = env.getTemplate("home");
        if (template == null) {
            return "Template not found";
        }
        // Simple placeholder replacement for demonstration
        String renderedTemplate = template.replace("{greeting}", request.getData("greeting"));
        return renderedTemplate;
    }

    public static String home(Environment env, Request request) {
        return render_response_from_env(env, request);
    }

    public static void main(String[] args) {
        Environment env = new Environment();
        Request request = new Request();

        env.setTemplate("home", "Hello, {greeting}!");
        request.setData("greeting", "World");

        String response = home(env, request);
        System.out.println(response); // Should print: Hello, World!
    }
}