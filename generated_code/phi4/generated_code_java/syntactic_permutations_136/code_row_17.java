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
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        String result = checkMod(username, password);

        response.setContentType("text/plain");
        response.getWriter().write(result);
    }

    private String checkMod(String username, String password) {
        if (USERNAME.equals(username) && PASSWORD.equals(password)) {
            return "true";
        } else {
            return "false";
        }
    }
}