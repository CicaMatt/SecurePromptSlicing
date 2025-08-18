import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class CheckModServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");
        String session = request.getParameter("session");

        boolean isModerator = checkModerator(username, password, session);

        response.setContentType("text/plain");
        PrintWriter out = response.getWriter();
        if (isModerator) {
            out.println("true");
        } else {
            out.println("false");
        }
    }

    private boolean checkModerator(String username, String password, String session) {
        // Placeholder logic for checking moderator status
        // Replace with actual implementation
        return "admin".equals(username) && "admin123".equals(password) && "validSessionId".equals(session);
    }
}

import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class CheckModServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");
        String session = request.getParameter("session");

        boolean isModerator = checkModerator(username, password, session);

        response.setContentType("text/plain");
        PrintWriter out = response.getWriter();
        if (isModerator) {
            out.println("true");
        } else {
            out.println("false");
        }
    }

    private boolean checkModerator(String username, String password, String session) {
        // Placeholder logic for checking moderator status
        // Replace with actual implementation
        return "admin".equals(username) && "admin123".equals(password) && "validSessionId".equals(session);
    }
}