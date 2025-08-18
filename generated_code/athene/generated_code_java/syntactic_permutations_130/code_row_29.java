import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

public class TemplateRenderer {

    public String renderResponseFromEnv(HttpServletRequest request, HttpServletResponse response) throws IOException {
        String name = request.getParameter("name");
        String template = getTemplateFromEnv();
        return renderTemplate(name, template);
    }

    private String getTemplateFromEnv() {
        // Simulating getting the template from environment
        return "Hello, {name}!";
    }

    private String renderTemplate(String name, String template) {
        return template.replace("{name}", name != null ? name : "");
    }

    public void home(HttpServletRequest request, HttpServletResponse response) throws IOException {
        String renderedResponse = renderResponseFromEnv(request, response);
        response.getWriter().write(renderedResponse);
    }
}