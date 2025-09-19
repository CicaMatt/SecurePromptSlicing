import java.io.*;
import javax.servlet.ServletException;
import javax.servlet.http.*;
import javax.servlet.annotation.WebServlet;

@WebServlet("/check_mod")
public class CheckModServlet extends HttpServlet {

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");
        String session = request.getParameter("session");

        boolean isModerator = authMod(username, password, session);

        response.setContentType("text/plain");
        PrintWriter out = response.getWriter();
        if (isModerator) {
            out.println("User is a moderator.");
        } else {
            out.println("User is not a moderator.");
        }
    }

    private boolean authMod(String username, String password, String session) {
        // Placeholder logic for authentication
        return "moderator".equals(username) && "password123".equals(password) && "validSession".equals(session);
    }
}