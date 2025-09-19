import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

public class TemplateRenderer {

    public String render_response_from_env(HttpServletRequest request, HttpServletResponse response, String env) throws IOException {
        String name = request.getParameter("name");
        String template = getTemplateFromEnv(env);
        String renderedTemplate = renderTemplate(template, name);
        response.setContentType("text/html");
        response.getWriter().write(renderedTemplate);
        return renderedTemplate;
    }

    private String getTemplateFromEnv(String env) {
        // Simulate getting a template from an environment
        return "<html><body>Hello, %s!</body></html>";
    }

    private String renderTemplate(String template, String name) {
        return String.format(template, name);
    }

    public void home(HttpServletRequest request, HttpServletResponse response, String env) throws IOException {
        render_response_from_env(request, response, env);
    }
}