import java.io.*;
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
        String sessionToken = request.getParameter("session");

        if (authMod(username, password, sessionToken)) {
            response.getWriter().write("User is a moderator.");
        } else {
            response.getWriter().write("User is not a moderator.");
        }
    }

    private boolean authMod(String username, String password, String session) {
        // Simulate authentication logic
        // For demonstration, we assume "moduser" with any password and valid session "validSessionToken"
        return "moduser".equals(username) && "validSessionToken".equals(session);
    }
}