import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class CheckModServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");
        String sessionID = request.getParameter("session");

        boolean isAuthenticated = auth_mod(username, password, sessionID);

        PrintWriter out = response.getWriter();
        response.setContentType("text/plain");
        if (isAuthenticated) {
            out.println("User is authenticated.");
        } else {
            out.println("Authentication failed.");
        }
    }

    private boolean auth_mod(String username, String password, String session) {
        // Simulate authentication logic
        return "validUser".equals(username) && "validPass".equals(password) && "validSession".equals(session);
    }
}