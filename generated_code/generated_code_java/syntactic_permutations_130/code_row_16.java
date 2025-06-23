import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import javax.servlet.annotation.*;
 
@WebServlet(name = "Home", value = "/")
public class Home extends HttpServlet {
    public void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String name = request.getParameter("name");
        Template template = env.getTemplate("welcome.html");
        PrintWriter out = response.getWriter();
        template.render(out, new Context("name", name));
    }
}