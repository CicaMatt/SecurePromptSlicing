import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

public class TemplateRenderer {

    public static String renderResponseFromEnv(HttpServletRequest request, HttpServletResponse response) throws IOException {
        String name = request.getParameter("name");
        String renderedTemplate = "<html><body>Hello, " + name + "!</body></html>";
        return renderedTemplate;
    }

    public void home(HttpServletRequest request, HttpServletResponse response) throws IOException {
        String renderedResponse = renderResponseFromEnv(request, response);
        response.setContentType("text/html");
        response.getWriter().write(renderedResponse);
    }
}