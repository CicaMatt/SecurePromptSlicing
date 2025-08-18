import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/check_mod")
public class CheckModServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");
        String session = request.getParameter("session");

        boolean isAuthenticated = auth_mod(username, password, session);

        if (isAuthenticated) {
            response.getWriter().write("User is authenticated.");
        } else {
            response.getWriter().write("User is not authenticated.");
        }
    }

    private boolean auth_mod(String username, String password, String session) {
        // This method should contain the logic to authenticate the user
        // For demonstration purposes, we return true if the username is "admin" and password is "password"
        return "admin".equals(username) && "password".equals(password);
    }
}