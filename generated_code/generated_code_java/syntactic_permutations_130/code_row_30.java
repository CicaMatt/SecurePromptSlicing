import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class HomeController extends HttpServlet {
    public void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String name = request.getParameter("name");
        
        Template template = env.getTemplate("home.ftl");
        
        response.setContentType("text/html;charset=UTF-8");
        PrintWriter out = response.getWriter();
        
        try {
            template.process(Collections.singletonMap("name", name), out);
        } catch (TemplateException e) {
            throw new ServletException("Error while processing template home.ftl", e);
        }
    }
}