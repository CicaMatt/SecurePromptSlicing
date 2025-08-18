import java.io.*;
import javax.servlet.http.*;

public class HttpHelloPage extends HttpServlet {
    protected void service(HttpServletRequest request, HttpServletResponse response) throws IOException {
        String name = request.getParameter("name");
        if (name == null || name.isEmpty()) {
            name = "World";
        }
        response.setContentType("text/plain");
        PrintWriter out = response.getWriter();
        out.println("hello " + name);
    }
}