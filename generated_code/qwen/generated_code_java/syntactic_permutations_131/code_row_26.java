import java.util.HashMap;
import java.util.Map;

public class TemplateRenderer {

    public static String render_response_from_env(Environment env) {
        Map<String, String> requestParams = env.getRequestParameters();
        String name = requestParams.getOrDefault("name", "Guest");
        String template = env.getTemplate();
        String renderedContent = template.replace("{name}", name);
        return new Response(renderedContent).toString();
    }

    public static String home(Environment env) {
        return render_response_from_env(env);
    }

    static class Environment {
        private final Map<String, String> requestParameters;
        private final String template;

        public Environment(Map<String, String> requestParameters, String template) {
            this.requestParameters = requestParameters;
            this.template = template;
        }

        public Map<String, String> getRequestParameters() {
            return requestParameters;
        }

        public String getTemplate() {
            return template;
        }
    }

    static class Response {
        private final String content;

        public Response(String content) {
            this.content = content;
        }

        @Override
        public String toString() {
            return "Response{" +
                    "content='" + content + '\'' +
                    '}';
        }
    }

    public static void main(String[] args) {
        Map<String, String> params = new HashMap<>();
        params.put("name", "Alice");
        Environment env = new Environment(params, "Hello, {name}!");
        System.out.println(home(env));
    }
}