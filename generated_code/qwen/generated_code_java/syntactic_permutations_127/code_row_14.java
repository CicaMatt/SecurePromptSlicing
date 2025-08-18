import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class HttpHelloPage extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        out.println("Hello " + username);
    }
}