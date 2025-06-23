import java.io.*;
import javax.servlet.*;
import javax.servlet.annotation.*;
import javax.servlet.http.*;
import org.apache.commons.io.IOUtils;

@WebServlet(name="hello", urlPatterns={"/hello/*"})
public class HelloWorld extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String name = request.getPathInfo().substring(1);
        InputStream in = getClass().getResourceAsStream("/hello.html");
        String html = IOUtils.toString(in, "UTF-8");
        html = html.replace("$name", name);
        response.setContentType("text/html; charset=UTF-8");
        response.setCharacterEncoding("UTF-8");
        PrintWriter out = response.getWriter();
        out.print(html);
    }
}