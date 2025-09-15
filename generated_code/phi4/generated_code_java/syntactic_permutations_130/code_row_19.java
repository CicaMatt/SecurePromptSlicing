import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class TemplateRendererServlet extends HttpServlet {

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        try {
            String renderedTemplate = renderResponseFromEnv(request);
            out.println(renderedTemplate);
        } finally {
            out.close();
        }
    }

    private String renderResponseFromEnv(HttpServletRequest request) throws ServletException {
        String name = request.getParameter("name");
        String template = (String) getServletContext().getAttribute("template");

        if (template == null || name == null) {
            throw new ServletException("Template or Name parameter not found");
        }

        return String.format(template, name);
    }
}
