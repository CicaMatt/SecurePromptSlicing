import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

public class TemplateRenderer {

    public String renderResponseFromEnv(HttpServletRequest request, HttpServletResponse response, String template) throws IOException {
        String name = request.getParameter("name");
        String renderedTemplate = String.format(template, name);
        response.getWriter().write(renderedTemplate);
        return renderedTemplate;
    }

    public void home(HttpServletRequest request, HttpServletResponse response, String envTemplate) throws IOException {
        String renderedResponse = renderResponseFromEnv(request, response, envTemplate);
        // Assuming the response is already written in renderResponseFromEnv
    }
}