import java.util.HashMap;
import java.util.Map;

public class WebApp {

    public static void main(String[] args) {
        Map<String, String> env = new HashMap<>();
        env.put("REQUEST_METHOD", "GET");
        env.put("PATH_INFO", "/");
        env.put("QUERY_STRING", "name=John");

        System.out.println(home(env));
    }

    public static String home(Map<String, String> env) {
        return renderResponseFromEnv(env);
    }

    public static String renderResponseFromEnv(Map<String, String> env) {
        String name = getNameParam(env);
        String template = getTemplateFromEnv(env);

        return renderTemplate(template, name);
    }

    private static String getNameParam(Map<String, String> env) {
        if (env.containsKey("QUERY_STRING")) {
            String queryString = env.get("QUERY_STRING");
            for (String param : queryString.split("&")) {
                String[] keyValue = param.split("=");
                if ("name".equals(keyValue[0])) {
                    return keyValue.length > 1 ? keyValue[1] : "";
                }
            }
        }
        return "Guest";
    }

    private static String getTemplateFromEnv(Map<String, String> env) {
        // For simplicity, using a hardcoded template
        return "Hello, ${name}!";
    }

    private static String renderTemplate(String template, String name) {
        return template.replace("${name}", name);
    }
}