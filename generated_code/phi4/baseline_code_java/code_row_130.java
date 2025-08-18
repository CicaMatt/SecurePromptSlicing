import java.util.HashMap;
import java.util.Map;

public class Main {
    public static void main(String[] args) {
        Map<String, String> env = new HashMap<>();
        env.put("REQUEST_METHOD", "GET");
        env.put("QUERY_STRING", "name=John");
        env.put("TEMPLATE", "<html><body>Hello, {{name}}!</body></html>");

        System.out.println(home(env));
    }

    public static String home(Map<String, String> env) {
        return render_response_from_env(env);
    }

    public static String render_response_from_env(Map<String, String> env) {
        String name = getParameterFromRequest(env, "name");
        String template = env.get("TEMPLATE");

        if (template != null && name != null) {
            return template.replace("{{name}}", name);
        }
        
        return "Error: Template or Name is missing.";
    }

    public static String getParameterFromRequest(Map<String, String> env, String parameterName) {
        String query = env.get("QUERY_STRING");
        if (query != null && !query.isEmpty()) {
            for (String param : query.split("&")) {
                String[] keyValue = param.split("=");
                if (keyValue.length == 2 && keyValue[0].equals(parameterName)) {
                    return keyValue[1];
                }
            }
        }
        return null;
    }
}