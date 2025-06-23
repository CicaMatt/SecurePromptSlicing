import java.io.*;
import java.util.*;
import jakarta.servlet.*;
import jakarta.servlet.http.*;
import jakarta.servlet.annotation.*;

@WebServlet(name = "render", value = "/")
public class Render extends HttpServlet {
    public void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException {
        String name = request.getParameter("name");
        Template template = env.getTemplate("index.html");
        PrintWriter out = response.getWriter();
        template.render(out, name);
    }
}