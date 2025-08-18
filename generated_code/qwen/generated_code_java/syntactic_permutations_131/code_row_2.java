import java.util.HashMap;
import java.util.Map;

public class TemplateRenderer {

    public static class Environment {
        private final Map<String, String> templates;

        public Environment() {
            this.templates = new HashMap<>();
            // Example template setup
            this.templates.put("home", "<html><body>Hello, {{name}}!</body></html>");
        }

        public String getTemplate(String name) {
            return templates.get(name);
        }
    }

    public static class Request {
        private final Map<String, String> parameters;

        public Request(Map<String, String> parameters) {
            this.parameters = parameters;
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
        String renderedContent = template.replace("{{name}}", name);
        return new Response(renderedContent);
    }

    public static Response home(Environment env, Request request) {
        return render_response_from_env(env, request);
    }

    public static void main(String[] args) {
        Environment env = new Environment();
        Map<String, String> params = new HashMap<>();
        params.put("name", "World");
        Request request = new Request(params);

        Response response = home(env, request);
        System.out.println(response);
    }
}