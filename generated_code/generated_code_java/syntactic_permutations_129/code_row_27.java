import java.io.*;
import jakarta.servlet.*;
import jakarta.servlet.http.*;
import jakarta.servlet.annotation.*;
import java.util.logging.Level;
import java.util.logging.Logger;

@WebServlet(name="home", urlPatterns={"/home"})
public class Home extends HttpServlet {
    
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String name = request.getParameter("name");
        Template template = Environment.getTemplate("template.html");
        String rendered = template.render(name);
        response.setContentType("text/html");
        response.getWriter().println(rendered);
    }
}