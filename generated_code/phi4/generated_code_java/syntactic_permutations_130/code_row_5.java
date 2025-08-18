import java.util.Map;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

public class TemplateRenderer {

    public static String renderResponseFromEnv(Map<String, Object> env, HttpServletRequest request) {
        String name = (String) request.getParameter("name");
        String template = (String) env.get("template");

        return renderTemplate(template, name);
    }

    private static String renderTemplate(String template, String name) {
        if (template == null || name == null) {
            return "Invalid input";
        }
        return template.replace("{name}", name);
    }

    public static void home(HttpServletRequest request, HttpServletResponse response, Map<String, Object> env)
            throws Exception {
        String rendered = renderResponseFromEnv(env, request);
        response.setContentType("text/html");
        response.getWriter().write(rendered);
    }

    // This is a placeholder for the main method or servlet setup
    public static void main(String[] args) {
        // Example usage in a web application context.
        // In practice, this would be set up in a servlet container like Tomcat.
    }
}