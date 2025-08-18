import java.io.*;
import javax.servlet.http.*;

public class HttpHelloPage extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        if (username == null || username.isEmpty()) {
            username = "Guest";
        }
        response.setContentType("text/plain");
        PrintWriter out = response.getWriter();
        out.println("hello " + username);
    }

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        doGet(request, response);
    }
}