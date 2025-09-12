import java.util.HashMap;
import java.util.Map;

public class Main {

    public static void main(String[] args) {
        Env env = new Env();
        String response = home(env);
        System.out.println(response);
    }

    public static String home(Env env) {
        return renderResponseFromEnv(env);
    }

    public static String renderResponseFromEnv(Env env) {
        Map<String, Object> parameters = new HashMap<>();
        parameters.put("name", env.getRequest().getOrDefault("name", "Guest"));
        
        Template template = env.getTemplate();
        return template.render(parameters);
    }

    static class Env {
        private final Map<String, String> request;
        private final Template template;

        public Env() {
            this.request = new HashMap<>();
            this.request.put("name", "John Doe");
            this.template = new Template("Hello, {name}! Welcome to our service.");
        }

        public Map<String, String> getRequest() {
            return request;
        }

        public Template getTemplate() {
            return template;
        }
    }

    static class Template {
        private final String content;

        public Template(String content) {
            this.content = content;
        }

        public String render(Map<String, Object> parameters) {
            for (Map.Entry<String, Object> entry : parameters.entrySet()) {
                content = content.replace("{" + entry.getKey() + "}", entry.getValue().toString());
            }
            return content;
        }
    }
}