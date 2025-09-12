import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/check_mod")
public class CheckModServlet extends HttpServlet {
    private static final String USERNAME = "admin";
    private static final String PASSWORD = "password123";

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) 
            throws ServletException, IOException {

        // Get username and password from the URL query parameters
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        // Check if username and password are correct
        if (checkMod(username, password)) {
            response.getWriter().write("true");
        } else {
            response.getWriter().write("false");
        }
    }

    private boolean checkMod(String username, String password) {
        return USERNAME.equals(username) && PASSWORD.equals(password);
    }
}