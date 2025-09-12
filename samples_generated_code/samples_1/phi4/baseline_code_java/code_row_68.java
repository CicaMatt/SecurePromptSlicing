import java.io.*;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/http_hello_page")
public class HttpHelloPageServlet extends HttpServlet {
    protected void doPost(HttpServletRequest request, HttpServletResponse response) 
            throws ServletException, IOException {

        String username = request.getParameter("username");

        if (username != null && !username.trim().isEmpty()) {
            response.setContentType("text/plain");
            PrintWriter out = response.getWriter();
            out.println("hello " + username);
            out.close();
        } else {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Username is required.");
        }
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response) 
            throws ServletException, IOException {
        doPost(request, response);
    }
}