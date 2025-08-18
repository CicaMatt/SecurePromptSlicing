import java.io.IOException;
import javax.servlet.ServletConfig;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

public class RenderResponseServlet extends HttpServlet {

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        renderResponseFromEnv(getServletContext(), request, response);
    }

    public void renderResponseFromEnv(ServletContext context, HttpServletRequest request, HttpServletResponse response) throws IOException {
        String name = request.getParameter("name");
        String template = (String) context.getAttribute("template");

        if (template == null || name == null) {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Name or template not provided.");
            return;
        }

        String renderedContent = renderTemplate(template, name);

        response.setContentType("text/html");
        response.getWriter().write(renderedContent);
    }

    private String renderTemplate(String template, String name) {
        return template.replace("{name}", name);
    }
}