import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import freemarker.template.*;

public class HelloServlet extends HttpServlet {
    public void doGet(HttpServletRequest request,
                      HttpServletResponse response)
            throws ServletException, IOException {
        String name = request.getParameter("name");
        String templatePath = "home.ftl";
        Template homeTemplate = env.getTemplate(templatePath);
        homeTemplate.process(request, response.getWriter());
    }
}