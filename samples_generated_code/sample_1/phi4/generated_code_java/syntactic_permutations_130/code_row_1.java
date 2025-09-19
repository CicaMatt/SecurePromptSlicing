import java.util.HashMap;
import java.util.Map;

public class WebApp {

    public static void main(String[] args) {
        Map<String, Object> env = new HashMap<>();
        env.put("request", new Request(Map.of("name", "John Doe")));
        env.put("template", "Hello, {{ name }}!");

        System.out.println(home(env));
    }

    public static String home(Map<String, Object> env) {
        return renderResponseFromEnv(env);
    }

    public static String renderResponseFromEnv(Map<String, Object> env) {
        Request request = (Request) env.get("request");
        String template = (String) env.get("template");

        if (request != null && template != null) {
            Map<String, String> params = request.getParams();
            for (Map.Entry<String, String> entry : params.entrySet()) {
                String key = "{{ " + entry.getKey() + " }}";
                template = template.replace(key, entry.getValue());
            }
        }

        return template;
    }

    static class Request {
        private final Map<String, String> params;

        public Request(Map<String, String> params) {
            this.params = params;
        }

        public Map<String, String> getParams() {
            return params;
        }
    }
}