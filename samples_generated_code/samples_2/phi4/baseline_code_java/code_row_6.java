import java.util.HashMap;
import java.util.Map;

public class TemplateRenderer {

    public static void main(String[] args) {
        Map<String, Object> env = new HashMap<>();
        env.put("request", new RequestParams("Alice"));
        env.put("template", "<html><body>Hello, {{name}}!</body></html>");

        String response = home(env);
        System.out.println(response);
    }

    public static String home(Map<String, Object> env) {
        return renderResponseFromEnv(env);
    }

    public static String renderResponseFromEnv(Map<String, Object> env) {
        RequestParams requestParams = (RequestParams) env.get("request");
        String template = (String) env.get("template");

        if (requestParams != null && template != null) {
            return template.replace("{{name}}", requestParams.getName());
        }

        return "Error: Missing parameters.";
    }

    static class RequestParams {
        private final String name;

        public RequestParams(String name) {
            this.name = name;
        }

        public String getName() {
            return name;
        }
    }
}