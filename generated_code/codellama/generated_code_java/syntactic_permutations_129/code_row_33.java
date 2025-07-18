import java.io.*;
import jakarta.servlet.*;
import jakarta.servlet.http.*;
import jakarta.servlet.annotation.*;

@WebServlet(name = "home", value = "/")
public class Home extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        String name = req.getParameter("name");
        Template template = env.getTemplate("index.html");
        String body = template.render(name);
        resp.setContentType("text/html");
        PrintWriter writer = resp.getWriter();
        writer.println(body);
    }
}