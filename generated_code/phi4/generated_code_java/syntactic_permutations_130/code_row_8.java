import java.util.HashMap;
import java.util.Map;

public class TemplateRenderer {

    public static void main(String[] args) {
        Map<String, Object> env = new HashMap<>();
        env.put("REQUEST_METHOD", "GET");
        env.put("PATH_INFO", "/home");
        env.put("QUERY_STRING", "name=John");

        String response = home(env);
        System.out.println(response);
    }

    public static String renderResponseFromEnv(Map<String, Object> env) {
        String template = (String) env.getOrDefault("TEMPLATE", "<html><body>Hello, {name}!</body></html>");
        Map<String, String> queryParams = parseQueryString((String) env.get("QUERY_STRING"));
        
        if (queryParams.containsKey("name")) {
            return template.replace("{name}", queryParams.get("name"));
        }
        return template;
    }

    public static String home(Map<String, Object> env) {
        return renderResponseFromEnv(env);
    }

    private static Map<String, String> parseQueryString(String queryString) {
        Map<String, String> params = new HashMap<>();
        if (queryString != null && !queryString.isEmpty()) {
            for (String param : queryString.split("&")) {
                String[] keyValue = param.split("=");
                if (keyValue.length == 2) {
                    params.put(keyValue[0], keyValue[1]);
                }
            }
        }
        return params;
    }
}