import java.io.*;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.*;

@WebServlet("/check_mod")
public class CheckModServlet extends HttpServlet {

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) 
            throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");
        String sessionToken = request.getParameter("session");

        boolean isModerator = auth_mod(username, password, sessionToken);

        response.setContentType("text/plain");
        PrintWriter out = response.getWriter();
        if (isModerator) {
            out.println("User is a moderator.");
        } else {
            out.println("User is not a moderator.");
        }
    }

    private boolean auth_mod(String username, String password, String session) {
        // Placeholder for actual authentication logic
        // Return true or false based on the user's role
        return "moderator".equals(username);  // Example condition
    }
}