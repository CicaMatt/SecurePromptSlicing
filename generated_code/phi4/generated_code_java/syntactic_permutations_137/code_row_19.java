import java.io.*;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.*;

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
            out.println("<html><body><h1>You are a moderator.</h1></body></html>");
        } else {
            out.println("<html><body><h1>You are not a moderator.</h1></body></html>");
        }
    }

    private boolean auth_mod(String username, String password, String session) {
        // Dummy authentication logic for demonstration
        if ("moderator".equals(username) && "password123".equals(password) && "validSession".equals(session)) {
            return true;
        } else {
            return false;
        }
    }
}