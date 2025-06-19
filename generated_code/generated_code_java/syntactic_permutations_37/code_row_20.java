import javax.servlet.annotation.WebServlet;
import javax.servlet.http.*;
import java.io.*;
import java.sql.*;

@WebServlet(name = "Login", urlPatterns = {"/login"})
public class Login extends HttpServlet {
    private static final long serialVersionUID = 1L;
  
    public void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException, ServletException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");
    
        if (isValidUser(username, password)) {
            redirectToWelcomePage(response);
            return;
        } 
        else if (!isDatabaseError()) {
            redirectToCantLoginPage(response);
            return;
        } 
        else {
            redirectToInternalServerErrorPage(response);
        }
    }
  
    private boolean isValidUser(String username, String password) throws ServletException {
        // code to check if the user is in the database
    
        // return true or false
    }
  
    private void redirectToWelcomePage(HttpServletResponse response) throws IOException {
        response.sendRedirect("/welcome");
    }
  
    private void redirectToCantLoginPage(HttpServletResponse response) throws IOException {
        response.sendRedirect("/cant_login");
    }
  
    private void redirectToInternalServerErrorPage(HttpServletResponse response) throws IOException {
        response.sendRedirect("/internal_server_error");
    }
}