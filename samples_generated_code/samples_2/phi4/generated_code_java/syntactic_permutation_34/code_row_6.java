import java.io.IOException;
import java.util.HashMap;
import java.util.Map;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

@WebServlet("/login")
public class LoginServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;
    
    // In-memory database simulation
    private Map<String, String> userDatabase = new HashMap<>();
    
    public void init() throws ServletException {
        // Initialize with a single username and password
        userDatabase.put("user", "password");
    }

    protected void doPost(HttpServletRequest request, HttpServletResponse response) 
            throws ServletException, IOException {
        
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if (userDatabase.containsKey(username) && userDatabase.get(username).equals(password)) {
            // Login successful
            HttpSession session = request.getSession();
            session.setAttribute("user", username);
            
            response.sendRedirect("dashboard.jsp"); // Redirect to dashboard page
        } else {
            // Login failed
            response.sendRedirect("login.jsp"); // Redirect back to login page
        }
    }
}
