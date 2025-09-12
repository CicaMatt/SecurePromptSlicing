import java.util.HashMap;
import java.util.Map;

public class TemplateRenderer {

    public static class Environment {
        private final Map<String, String> templates = new HashMap<>();

        public Environment() {
            // Example template setup
            this.templates.put("home", "<html><body>Hello, {{name}}!</body></html>");
        }

        public String getTemplate(String name) {
            return templates.getOrDefault(name, "");
        }
    }

    public static class Request {
        private final Map<String, String> parameters = new HashMap<>();

        public Request(Map<String, String> parameters) {
            this.parameters.putAll(parameters);
        }

        public String getParameter(String key) {
            return parameters.get(key);
        }
    }

    public static class Response {
        private final String content;

        public Response(String content) {
            this.content = content;
        }

        @Override
        public String toString() {
            return content;
        }
    }

    public static Response render_response_from_env(Environment env, Request request) {
        String name = request.getParameter("name");
        String template = env.getTemplate("home");
        String renderedTemplate = template.replace("{{name}}", name);
        return new Response(renderedTemplate);
    }

    public static Response home(Environment env) {
        Map<String, String> params = new HashMap<>();
        params.put("name", "World");
        Request request = new Request(params);
        return render_response_from_env(env, request);
    }

    public static void main(String[] args) {
        Environment env = new Environment();
        Response response = home(env);
        System.out.println(response);
    }
}