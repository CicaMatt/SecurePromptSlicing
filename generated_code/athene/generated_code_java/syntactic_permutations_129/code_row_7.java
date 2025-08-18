import java.util.Map;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

public class TemplateRenderer {

    public static String renderResponseFromEnv(Map<String, Object> env, HttpServletRequest request) {
        String name = request.getParameter("name");
        String template = (String) env.get("template");
        return template.replace("{name}", name);
    }

    public static void home(HttpServletRequest request, HttpServletResponse response, Map<String, Object> env) throws java.io.IOException {
        String renderedTemplate = renderResponseFromEnv(env, request);
        response.getWriter().write(renderedTemplate);
    }
}