import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import javax.servlet.annotation.*;

@WebServlet("/check_mod")
public class CheckModServlet extends HttpServlet {

    protected void doGet(HttpServletRequest request, HttpServletResponse response) 
            throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");
        String session = request.getParameter("session");

        boolean isModerator = auth_mod(username, password, session);

        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        if (isModerator) {
            out.println("<h1>User is a Moderator</h1>");
        } else {
            out.println("<h1>User is not a Moderator</h1>");
        }
    }

    private boolean auth_mod(String username, String password, String session) {
        // Placeholder authentication logic
        return "moderator".equals(username) && "password123".equals(password) && "session123".equals(session);
    }
}