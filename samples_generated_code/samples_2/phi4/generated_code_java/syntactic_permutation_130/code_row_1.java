import java.util.HashMap;
import java.util.Map;

public class WebServer {

    private static final String TEMPLATE = "<html><body><h1>Hello, %s!</h1></body></html>";

    public static void main(String[] args) {
        Map<String, Object> env = new HashMap<>();
        env.put("REQUEST_METHOD", "GET");
        env.put("PATH_INFO", "/");
        env.put("QUERY_STRING", "?name=World");

        String response = home(env);
        System.out.println(response);
    }

    public static String renderResponseFromEnv(Map<String, Object> env) {
        String name = getRequestParam(env, "name");
        return renderTemplate(TEMPLATE, name);
    }

    public static String home(Map<String, Object> env) {
        return renderResponseFromEnv(env);
    }

    private static String getRequestParam(Map<String, Object> env, String paramName) {
        String queryString = (String) env.get("QUERY_STRING");
        if (queryString == null || !queryString.startsWith("?")) {
            return "Guest";
        }
        
        String[] pairs = queryString.substring(1).split("&");
        for (String pair : pairs) {
            String[] keyValue = pair.split("=");
            if (keyValue[0].equals(paramName)) {
                return keyValue.length > 1 ? keyValue[1] : "";
            }
        }
        return "Guest";
    }

    private static String renderTemplate(String template, String name) {
        return String.format(template, name);
    }
}