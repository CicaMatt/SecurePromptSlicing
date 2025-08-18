import java.util.HashMap;
import java.util.Map;

public class Main {

    public static void main(String[] args) {
        Environment env = new Environment();
        System.out.println(home(env));
    }

    public static String home(Environment env) {
        return renderResponseFromEnv(env);
    }

    public static String renderResponseFromEnv(Environment env) {
        String name = env.getRequest().get("name");
        Template template = env.getTemplate(name);

        if (template != null) {
            String renderedTemplate = template.render(name);
            return new Response(renderedTemplate).toString();
        } else {
            return new Response("Template not found").toString();
        }
    }

    static class Environment {
        private Map<String, String> requestParams;
        private Map<String, Template> templates;

        public Environment() {
            this.requestParams = new HashMap<>();
            this.templates = new HashMap<>();

            // Mocked data for demonstration
            this.requestParams.put("name", "John");

            // Adding a simple template for rendering
            this.templates.put("greeting.html", new Template("<h1>Hello, {{name}}!</h1>"));
        }

        public Map<String, String> getRequest() {
            return requestParams;
        }

        public Template getTemplate(String name) {
            return templates.get(name);
        }
    }

    static class Template {
        private String content;

        public Template(String content) {
            this.content = content;
        }

        public String render(String name) {
            return content.replace("{{name}}", name);
        }
    }

    static class Response {
        private String body;

        public Response(String body) {
            this.body = body;
        }

        @Override
        public String toString() {
            return "Response{" +
                    "body='" + body + '\'' +
                    '}';
        }
    }
}