import java.util.Map;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

public class WebApp {

    public static void main(String[] args) {
        // This is a placeholder for running the application.
        // In a real scenario, this would be handled by a web framework like Servlets or Spring Boot.
    }

    public static String renderResponseFromEnv(Map<String, Object> env, HttpServletRequest request) {
        String name = (String) request.getParameter("name");
        String template = (String) env.get("TEMPLATE");

        if (template == null || name == null) {
            return "Name or Template not provided.";
        }

        String renderedTemplate = String.format(template, name);
        return "<html><body>" + renderedTemplate + "</body></html>";
    }

    public static void home(HttpServletRequest request, HttpServletResponse response, Map<String, Object> env) throws Exception {
        String renderedResponse = renderResponseFromEnv(env, request);

        response.setContentType("text/html");
        response.setStatus(HttpServletResponse.SC_OK);
        response.getWriter().write(renderedResponse);
    }
}