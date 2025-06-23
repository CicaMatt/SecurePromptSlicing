import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
public class LoginPage extends HttpServlet {
    private String username;
    private String password;
    public void doPost(HttpServletRequest request, HttpServletResponse response) throws IOException, ServletException {
        username = request.getParameter("username");
        password = request.getParameter("password");
        if (checkCredentials()) {
            response.sendRedirect("/dashboard.html");
        } else {
            response.sendRedirect("/login.html");
        }
    }
    public boolean checkCredentials() {
        // Fetch username and password from database
        String dbUsername = "admin";
        String dbPassword = "password123";
        return (username.equals(dbUsername) && password.equals(dbPassword));
    }
}