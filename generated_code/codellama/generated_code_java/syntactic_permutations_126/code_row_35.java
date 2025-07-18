import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class HelloServlet extends HttpServlet {
    public void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException, ServletException {
        String username = request.getParameter("username");
        PrintWriter out = response.getWriter();
        out.println("<html><body>Hello " + username + "</body></html>");
    }
}