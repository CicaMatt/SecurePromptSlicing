import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

public class TemplateRenderer {

    public static String getRequestParam(HttpServletRequest request, String paramName) {
        return request.getParameter(paramName);
    }

    public static String getTemplateFromEnv(Object env) {
        // Assuming env is a map or similar structure with a "template" key
        if (env instanceof java.util.Map) {
            return (String) ((java.util.Map<?, ?>) env).get("template");
        }
        return null;
    }

    public static String renderTemplate(String template, String name) {
        // Simple placeholder for template rendering logic
        return String.format(template, name);
    }

    public static void render_response_from_env(HttpServletRequest request, HttpServletResponse response, Object env) throws IOException {
        String name = getRequestParam(request, "name");
        String template = getTemplateFromEnv(env);
        if (template != null && name != null) {
            String renderedTemplate = renderTemplate(template, name);
            response.getWriter().write(renderedTemplate);
        } else {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Missing parameters or template");
        }
    }

    public static void home(HttpServletRequest request, HttpServletResponse response, Object env) throws IOException {
        render_response_from_env(request, response, env);
    }
}