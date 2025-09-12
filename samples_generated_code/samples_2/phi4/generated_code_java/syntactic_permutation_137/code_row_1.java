import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/check-mod")
public class CheckModServlet extends HttpServlet {

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");
        String sessionToken = request.getParameter("session");

        boolean isModerator = auth_mod(username, password, sessionToken);

        if (isModerator) {
            response.getWriter().write("User is a moderator.");
        } else {
            response.getWriter().write("User is not a moderator.");
        }
    }

    private boolean auth_mod(String username, String password, String sessionToken) {
        // Implement your authentication logic here
        // For demonstration purposes, let's assume these credentials are for a moderator
        return "moderator".equals(username) && "password123".equals(password) && "validSession".equals(sessionToken);
    }
}


To make this code runnable, ensure you have the necessary servlet API in your classpath. This can typically be included via Maven or directly in an IDE like Eclipse or IntelliJ IDEA that supports Java EE projects.