import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

public class TemplateRenderer {

    public static String render_response_from_env(HttpServletRequest request, HttpServletResponse response, Object env) throws IOException {
        String name = request.getParameter("name");
        String renderedTemplate = getFromEnvironment(env, "template");
        String finalTemplate = renderedTemplate.replace("{name}", name);
        response.getWriter().write(finalTemplate);
        return finalTemplate;
    }

    private static String getFromEnvironment(Object env, String key) {
        if (env instanceof java.util.Map) {
            return ((java.util.Map<String, String>) env).get(key);
        }
        throw new IllegalArgumentException("Environment is not a Map");
    }

    public static void home(HttpServletRequest request, HttpServletResponse response, Object env) throws IOException {
        String result = render_response_from_env(request, response, env);
        // Assuming the response body should be set with the rendered template
        response.getWriter().write(result);
    }
}