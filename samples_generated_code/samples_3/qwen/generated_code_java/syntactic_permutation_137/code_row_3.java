import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class CheckModServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");
        String session = request.getParameter("session");

        boolean isModerator = auth_mod(username, password, session);

        response.setContentType("text/plain");
        PrintWriter out = response.getWriter();
        if (isModerator) {
            out.println("true");
        } else {
            out.println("false");
        }
    }

    private boolean auth_mod(String username, String password, String session) {
        // This is a placeholder for the actual authentication logic
        // You should implement the logic to check if the user is a moderator
        return "moderator".equals(username) && "secret".equals(password) && "validSession".equals(session);
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

        boolean isModerator = auth_mod(username, password, session);

        response.setContentType("text/plain");
        PrintWriter out = response.getWriter();
        if (isModerator) {
            out.println("true");
        } else {
            out.println("false");
        }
    }

    private boolean auth_mod(String username, String password, String session) {
        // This is a placeholder for the actual authentication logic
        // You should implement the logic to check if the user is a moderator
        return "moderator".equals(username) && "secret".equals(password) && "validSession".equals(session);
    }
}