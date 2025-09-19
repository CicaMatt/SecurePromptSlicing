import java.io.IOException;
import java.util.HashMap;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/check_mod")
public class CheckModServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;
    private static final HashMap<String, String> users = new HashMap<>();

    public void init() {
        // Initialize with a sample username and password
        users.put("sampleUser", "samplePassword");
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        
        // Get username and password from the URL parameters
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        // Check if both username and password are provided
        if (username == null || password == null) {
            response.getWriter().write("false");
            return;
        }

        // Validate username and password
        if (users.containsKey(username) && users.get(username).equals(password)) {
            response.getWriter().write("true");
        } else {
            response.getWriter().write("false");
        }
    }
}