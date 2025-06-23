import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

@WebServlet(urlPatterns = {"/hello/*"})
public class HelloWorld extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        String username = request.getPathInfo().replace("/", "");
        response.getWriter().print("Hello " + escape(username) + "!");
    }

    protected String escape(String s) {
        // ...
    }
}