import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/check_mod")
public class CheckModServlet extends HttpServlet {
    
    protected void doGet(HttpServletRequest request, HttpServletResponse response) 
            throws ServletException, IOException {

        String username = request.getParameter("username");
        String password = request.getParameter("password");
        String session = request.getParameter("session");

        if (authMod(username, password, session)) {
            response.getWriter().write("User is a moderator.");
        } else {
            response.getWriter().write("User is not a moderator.");
        }
    }

    private boolean authMod(String username, String password, String session) {
        // Dummy authentication logic
        return "moderator".equals(username) && "password123".equals(password) && "validSession".equals(session);
    }
}


Make sure to include the necessary web.xml configuration or use servlet annotations as shown above. This code assumes a simple in-memory check for demonstration purposes. In a real application, you would replace this with proper authentication logic, possibly involving database queries and session management.