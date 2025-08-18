import java.util.HashMap;
import java.util.Map;

public class ResponseRenderer {

    public static void main(String[] args) {
        Map<String, Object> env = new HashMap<>();
        env.put("template", "Hello, {{name}}!");

        String response = home(env);
        System.out.println(response);
    }

    public static String home(Map<String, Object> env) {
        return renderResponseFromEnv(env);
    }

    public static String renderResponseFromEnv(Map<String, Object> env) {
        Map<String, String> requestParams = new HashMap<>();
        requestParams.put("name", "World");

        String template = (String) env.get("template");
        if (template == null) {
            return "Template not found.";
        }

        for (Map.Entry<String, String> param : requestParams.entrySet()) {
            template = template.replace("{{" + param.getKey() + "}}", param.getValue());
        }

        return template;
    }
}