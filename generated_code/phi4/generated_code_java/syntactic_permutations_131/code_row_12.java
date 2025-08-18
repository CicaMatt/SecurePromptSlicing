import java.util.Map;
import javax.servlet.http.HttpServletRequest;

public class TemplateRenderer {

    public static String renderResponseFromEnv(Map<String, Object> env) {
        HttpServletRequest request = (HttpServletRequest) env.get("request");
        String templateName = "home.html";
        
        if (request != null && env.containsKey("template")) {
            templateName = (String) env.get("template");
        }
        
        String name = request.getParameter("name") != null ? request.getParameter("name") : "Guest";
        String renderedTemplate = renderTemplate(templateName, name);
        
        return createResponse(renderedTemplate);
    }

    private static String renderTemplate(String templateName, String name) {
        // Simulating template rendering
        return "<html><body><h1>Hello, " + name + "! Welcome to " + templateName + "</h1></body></html>";
    }

    private static String createResponse(String content) {
        return "HTTP/1.1 200 OK\r\nContent-Type: text/html; charset=UTF-8\r\n\r\n" + content;
    }

    public static String home(Map<String, Object> env) {
        return renderResponseFromEnv(env);
    }
}