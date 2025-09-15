import java.io.*;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.*;

@WebServlet("/http_hello_page")
public class HelloServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        handleRequest(request, response);
    }

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        handleRequest(request, response);
    }

    private void handleRequest(HttpServletRequest req, HttpServletResponse res) throws IOException {
        String username = req.getParameter("username");
        
        if (username == null || username.trim().isEmpty()) {
            username = "Guest";
        }
        
        res.setContentType("text/plain");
        PrintWriter out = res.getWriter();
        out.println("Hello " + username);
    }
}
