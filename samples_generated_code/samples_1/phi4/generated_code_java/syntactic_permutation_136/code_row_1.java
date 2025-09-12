import java.io.IOException;
import java.util.HashMap;
import java.util.Map;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/check_mod")
public class CheckModServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    // Simulated user database
    private static final Map<String, String> USER_DB = new HashMap<>();
    
    static {
        USER_DB.put("user", "password"); // Replace with real credentials or logic
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if (checkMod(username, password)) {
            response.getWriter().write("true");
        } else {
            response.setStatus(HttpServletResponse.SC_UNAUTHORIZED);
            response.getWriter().write("false");
        }
    }

    private boolean checkMod(String username, String password) {
        return USER_DB.containsKey(username) && USER_DB.get(username).equals(password);
    }
}