import java.io.*;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/check_mod")
public class CheckModServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

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
        // Dummy authentication logic for demonstration purposes
        return "admin".equals(username) && "password123".equals(password) && "validSession".equals(session);
    }
}