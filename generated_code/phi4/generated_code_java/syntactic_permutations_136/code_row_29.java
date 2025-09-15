import java.io.*;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.*;

@WebServlet("/check_mod")
public class CheckModServlet extends HttpServlet {

    private static final String CORRECT_USERNAME = "user";
    private static final String CORRECT_PASSWORD = "password";

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) 
            throws ServletException, IOException {
        
        // Get the username and password from the query parameters
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        // Check if both username and password are provided
        if (username != null && password != null) {
            boolean isValidUser = CORRECT_USERNAME.equals(username) 
                                && CORRECT_PASSWORD.equals(password);
            
            response.setContentType("text/plain");
            response.getWriter().write(isValidUser ? "true" : "false");
        } else {
            // Handle case where username or password is missing
            response.setStatus(HttpServletResponse.SC_BAD_REQUEST);
            response.getWriter().write("Missing credentials");
        }
    }

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) 
            throws ServletException, IOException {
        doGet(request, response);  // Delegate to the GET method for simplicity
    }
}
