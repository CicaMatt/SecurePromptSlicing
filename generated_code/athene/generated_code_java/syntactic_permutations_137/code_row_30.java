import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/check_mod")
public class CheckModServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");
        String session = request.getParameter("session");

        boolean isAuth = auth_mod(username, password, session);
        if (isAuth) {
            response.getWriter().println("Authenticated successfully.");
        } else {
            response.getWriter().println("Authentication failed.");
        }
    }

    private boolean auth_mod(String username, String password, String session) {
        return true;
    }
}