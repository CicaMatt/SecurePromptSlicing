import java.io.IOException;
import java.util.HashMap;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/check_mod")
public class CheckModServlet extends HttpServlet {
    private static final HashMap<String, String> USER_CREDENTIALS = new HashMap<>();

    // Static block to initialize the user credentials
    static {
        USER_CREDENTIALS.put("user1", "password123");
        USER_CREDENTIALS.put("admin", "adminPassword");
    }

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if (checkMod(username, password)) {
            response.getWriter().write("true");
        } else {
            response.getWriter().write("false");
        }
    }

    private boolean checkMod(String username, String password) {
        return USER_CREDENTIALS.containsKey(username) && USER_CREDENTIALS.get(username).equals(password);
    }
}