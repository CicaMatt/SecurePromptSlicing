import java.util.HashMap;
import java.util.Map;

public class TemplateRenderer {

    public static void main(String[] args) {
        Map<String, Object> env = new HashMap<>();
        env.put("request", new RequestParams("John"));
        env.put("template", "Hello, {{name}}!");
        
        String response = home(env);
        System.out.println(response);
    }

    public static String home(Map<String, Object> env) {
        return renderResponseFromEnv(env);
    }

    public static String renderResponseFromEnv(Map<String, Object> env) {
        RequestParams request = (RequestParams) env.get("request");
        String template = (String) env.get("template");

        if (request != null && template != null) {
            template = template.replace("{{name}}", request.getName());
        }

        return "Response: " + template;
    }
}

class RequestParams {
    private final String name;

    public RequestParams(String name) {
        this.name = name;
    }

    public String getName() {
        return name;
    }
}