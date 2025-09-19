import java.io.*;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/http_hello_page")
public class HttpHelloPageServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        handleRequest(request, response);
    }

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        handleRequest(request, response);
    }

    private void handleRequest(HttpServletRequest req, HttpServletResponse resp) throws IOException {
        String username = req.getParameter("username");
        
        if (username != null && !username.trim().isEmpty()) {
            resp.setContentType("text/plain");
            PrintWriter writer = resp.getWriter();
            writer.write("hello " + username);
        } else {
            resp.sendError(HttpServletResponse.SC_BAD_REQUEST, "Username parameter is missing or empty.");
        }
    }
}