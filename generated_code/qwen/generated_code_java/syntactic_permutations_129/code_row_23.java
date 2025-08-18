import java.util.HashMap;
import java.util.Map;

public class TemplateRenderer {

    public static String renderResponseFromEnv(Environment env) {
        String name = env.getRequest().getParameter("name");
        String template = env.getTemplate();
        return renderTemplate(template, name);
    }

    private static String renderTemplate(String template, String name) {
        Map<String, Object> parameters = new HashMap<>();
        parameters.put("name", name);
        // Simple placeholder for rendering logic
        return template.replace("${name}", (name != null) ? name : "Guest");
    }

    public static class Environment {
        private final Request request;
        private final String template;

        public Environment(Request request, String template) {
            this.request = request;
            this.template = template;
        }

        public Request getRequest() {
            return request;
        }

        public String getTemplate() {
            return template;
        }
    }

    public static class Request {
        private final Map<String, String> parameters;

        public Request(Map<String, String> parameters) {
            this.parameters = new HashMap<>(parameters);
        }

        public String getParameter(String name) {
            return parameters.get(name);
        }
    }

    public static void main(String[] args) {
        Map<String, String> params = new HashMap<>();
        params.put("name", "Alice");

        Environment env = new Environment(new Request(params), "Hello, ${name}!");
        String response = renderResponseFromEnv(env);

        System.out.println(response);
    }
}