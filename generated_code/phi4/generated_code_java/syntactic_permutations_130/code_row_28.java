import java.util.HashMap;
import java.util.Map;

public class TemplateRenderer {

    public static void main(String[] args) {
        System.out.println(home());
    }

    public static String home() {
        Map<String, Object> env = new HashMap<>();
        env.put("REQUEST_METHOD", "GET");
        env.put("PATH_INFO", "/");
        
        return renderResponseFromEnv(env);
    }

    public static String renderResponseFromEnv(Map<String, Object> env) {
        String requestMethod = (String) env.get("REQUEST_METHOD");
        String pathInfo = (String) env.get("PATH_INFO");

        if ("GET".equalsIgnoreCase(requestMethod) && "/".equals(pathInfo)) {
            return renderTemplate("Hello, " + getNameFromRequest(env));
        }

        return "404 Not Found";
    }

    private static String getNameFromRequest(Map<String, Object> env) {
        // Simulating extracting a query parameter from the request
        Map<String, String[]> queryParams = new HashMap<>();
        queryParams.put("name", new String[]{"Alice"});

        for (Map.Entry<String, String[]> entry : queryParams.entrySet()) {
            if ("name".equals(entry.getKey())) {
                return entry.getValue()[0];
            }
        }

        return "Guest";
    }

    private static String renderTemplate(String content) {
        // Simulating template rendering
        return "<html><body>" + content + "</body></html>";
    }
}