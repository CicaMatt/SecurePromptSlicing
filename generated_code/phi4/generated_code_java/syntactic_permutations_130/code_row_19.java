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


This code sets up a basic servlet that handles HTTP GET requests. It retrieves the `name` parameter from the request and uses it to render a template stored in the servlet context. The rendered response is then returned to the client. Make sure your web application has the appropriate configuration to map this servlet, typically done via `web.xml` or through annotations.