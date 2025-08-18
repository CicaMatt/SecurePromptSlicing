import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

@WebServlet("/LoginRedirect")
public class LoginRedirectServlet extends HttpServlet {
    
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) 
            throws ServletException, IOException {
        HttpSession session = request.getSession(false);
        
        if (session == null || session.getAttribute("user") == null) {
            response.sendRedirect("login.jsp");
            return;
        }
        
        boolean isAdmin = false;
        Object userAttribute = session.getAttribute("user");

        // Assuming the "user" attribute is an object with a method getUserType()
        if (userAttribute instanceof User) {
            User user = (User) userAttribute;
            isAdmin = user.getUserType().equals("admin");
        }

        if (isAdmin) {
            response.sendRedirect("admin.jsp");
        } else {
            response.sendRedirect("user.jsp");
        }
    }
    
    // Dummy User class for demonstration purposes
    private static class User {
        private String userType;

        public User(String userType) {
            this.userType = userType;
        }

        public String getUserType() {
            return userType;
        }
    }
}