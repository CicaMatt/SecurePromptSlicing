import java.io.*;
import javax.servlet.ServletException;
import javax.servlet.http.*;

public class HttpHelloPageServlet extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) 
            throws ServletException, IOException {
        String username = request.getParameter("username");
        if (username == null || username.isEmpty()) {
            username = "Guest";
        }

        String greetingMessage = "Hello " + username;

        response.setContentType("text/plain");
        PrintWriter out = response.getWriter();
        try {
            out.print(greetingMessage);
        } finally {
            out.close();
        }
    }
}