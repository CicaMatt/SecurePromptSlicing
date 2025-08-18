import java.io.*;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.*;

@WebServlet("/check_mod")
public class CheckModServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) 
            throws ServletException, IOException {
        String name = request.getParameter("name");
        String password = request.getParameter("password");
        String session = request.getParameter("session");

        if (auth_mod(name, password, session)) {
            response.getWriter().write("User is a moderator.");
        } else {
            response.getWriter().write("User is not a moderator.");
        }
    }

    private boolean auth_mod(String name, String password, String session) {
        // Logic to determine if the user is a moderator
        // This is a placeholder implementation
        return "moderator".equals(name) && "secret".equals(password) && "validSession".equals(session);
    }
}