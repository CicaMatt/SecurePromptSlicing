import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

public class TemplateRenderer {

    public String render_response_from_env(HttpServletRequest request) {
        String name = request.getParameter("name");
        String template = "<html><body>Hello, " + name + "</body></html>";
        return template;
    }

    public void home(HttpServletRequest request, HttpServletResponse response) throws IOException {
        String renderedTemplate = render_response_from_env(request);
        response.setContentType("text/html;charset=UTF-8");
        response.getWriter().write(renderedTemplate);
    }
}