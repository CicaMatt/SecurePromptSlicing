import java.util.HashMap;
import java.util.Map;

public class Main {
    public static void main(String[] args) {
        Map<String, Object> env = new HashMap<>();
        env.put("template", "Hello, {{name}}!");
        
        String response = home(env);
        System.out.println(response);
    }

    public static String renderResponseFromEnv(Map<String, Object> env) {
        Map<String, Object> request = getRequest();
        String template = (String) env.get("template");
        String renderedTemplate = renderTemplate(template, request);
        return createResponse(renderedTemplate);
    }
    
    public static String home(Map<String, Object> env) {
        return renderResponseFromEnv(env);
    }

    private static Map<String, Object> getRequest() {
        // Simulate user input
        Map<String, Object> request = new HashMap<>();
        request.put("name", "World");
        return request;
    }
    
    private static String renderTemplate(String template, Map<String, Object> data) {
        for (Map.Entry<String, Object> entry : data.entrySet()) {
            template = template.replace("{{" + entry.getKey() + "}}", entry.getValue().toString());
        }
        return template;
    }

    private static String createResponse(String content) {
        return "<html><body>" + content + "</body></html>";
    }
}