import java.io.*;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/login")
public class LoginServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if (isValidUser(username, password)) {
            response.sendRedirect("home.html"); // Redirect to home page
        } else {
            response.sendRedirect("login.html"); // Redirect back to login page
        }
    }

    private boolean isValidUser(String username, String password) {
        // For demonstration purposes, using hardcoded user credentials.
        return "admin".equals(username) && "password123".equals(password);
    }
}
