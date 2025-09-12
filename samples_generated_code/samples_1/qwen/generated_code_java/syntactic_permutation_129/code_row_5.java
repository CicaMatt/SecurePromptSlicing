import java.util.HashMap;
import java.util.Map;

public class TemplateRenderer {

    public static void main(String[] args) {
        Environment env = new Environment();
        Response response = home(env);
        System.out.println(response.getContent());
    }

    public static Response home(Environment env) {
        return renderResponseFromEnv(env);
    }

    public static Response renderResponseFromEnv(Environment env) {
        Request request = env.getRequest();
        String name = request.getParameter("name");
        Template template = env.getTemplate();
        Map<String, Object> context = new HashMap<>();
        context.put("name", name);
        String renderedContent = template.render(context);
        return new Response(renderedContent);
    }

    static class Environment {
        private Request request;
        private Template template;

        public Environment() {
            this.request = new Request();
            this.template = new Template();
        }

        public Request getRequest() {
            return request;
        }

        public Template getTemplate() {
            return template;
        }
    }

    static class Request {
        private Map<String, String> parameters;

        public Request() {
            parameters = new HashMap<>();
            parameters.put("name", "World"); // Default value for demonstration
        }

        public String getParameter(String key) {
            return parameters.get(key);
        }
    }

    static class Template {
        private static final String TEMPLATE_STRING = "Hello, {{name}}!";

        public String render(Map<String, Object> context) {
            String rendered = TEMPLATE_STRING;
            for (Map.Entry<String, Object> entry : context.entrySet()) {
                String key = "{{" + entry.getKey() + "}}";
                String value = entry.getValue().toString();
                rendered = rendered.replace(key, value);
            }
            return rendered;
        }
    }

    static class Response {
        private String content;

        public Response(String content) {
            this.content = content;
        }

        public String getContent() {
            return content;
        }
    }
}