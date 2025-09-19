import java.util.HashMap;
import java.util.Map;

public class TemplateRenderer {

    public static String renderResponseFromEnv(Map<String, Object> env) {
        Map<String, String[]> requestParameters = (Map<String, String[]>) env.get("request_parameters");
        
        if (requestParameters == null || !requestParameters.containsKey("name")) {
            return "Name parameter is missing in the request.";
        }
        
        String name = requestParameters.get("name")[0];
        String template = (String) env.get("template");

        if (template == null) {
            return "Template is not provided in the environment.";
        }

        // Simple string replacement for demonstration
        String renderedTemplate = template.replace("{name}", name);
        
        return buildHttpResponse(200, "OK", renderedTemplate);
    }

    public static String home(Map<String, Object> env) {
        return renderResponseFromEnv(env);
    }
    
    private static String buildHttpResponse(int statusCode, String statusMessage, String body) {
        StringBuilder response = new StringBuilder();
        response.append("HTTP/1.1 ").append(statusCode).append(" ").append(statusMessage).append("\r\n");
        response.append("Content-Type: text/html\r\n");
        response.append("Content-Length: ").append(body.length()).append("\r\n");
        response.append("\r\n");
        response.append(body);
        
        return response.toString();
    }

    public static void main(String[] args) {
        Map<String, Object> env = new HashMap<>();
        env.put("template", "Hello, {name}!");
        
        // Simulating a request with a name parameter
        Map<String, String[]> requestParameters = new HashMap<>();
        requestParameters.put("name", new String[]{"John"});
        env.put("request_parameters", requestParameters);

        System.out.println(home(env));
    }
}