import java.util.HashMap;
import java.util.Map;

public class TemplateRenderer {

    public static void main(String[] args) {
        Map<String, String> env = new HashMap<>();
        env.put("REQUEST_METHOD", "GET");
        env.put("PATH_INFO", "/");
        env.put("QUERY_STRING", "name=John");

        String response = home(env);
        System.out.println(response);
    }

    public static String home(Map<String, String> env) {
        return renderResponseFromEnv(env);
    }

    public static String renderResponseFromEnv(Map<String, String> env) {
        String name = getNameParameter(env);

        String template = getTemplate(env);
        
        String renderedTemplate = renderTemplate(template, name);
        
        return createResponse(renderedTemplate);
    }
    
    private static String getNameParameter(Map<String, String> env) {
        String queryString = env.get("QUERY_STRING");
        if (queryString != null && !queryString.isEmpty()) {
            for (String param : queryString.split("&")) {
                String[] keyValue = param.split("=");
                if ("name".equals(keyValue[0])) {
                    return keyValue.length > 1 ? keyValue[1] : "";
                }
            }
        }
        return "Guest";
    }

    private static String getTemplate(Map<String, String> env) {
        // Assuming a simple template for demonstration purposes
        return "<html><body>Hello, {name}!</body></html>";
    }

    private static String renderTemplate(String template, String name) {
        return template.replace("{name}", name);
    }

    private static String createResponse(String content) {
        return "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n" + content;
    }
}