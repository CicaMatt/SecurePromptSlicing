import java.io.IOException;
import java.util.HashMap;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/")
public class LoginServlet extends HttpServlet {
    
    private static final HashMap<String, String> userCredentials = new HashMap<>();
    
    static {
        // Predefined username and password for demonstration
        userCredentials.put("admin", "password123");
    }

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) 
            throws ServletException, IOException {
        
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if (isLoginSuccessful(username, password)) {
            response.getWriter().write("true");
        } else {
            response.getWriter().write("false");
        }
    }

    private boolean isLoginSuccessful(String username, String password) {
        return userCredentials.containsKey(username) && 
               userCredentials.get(username).equals(password);
    }
}