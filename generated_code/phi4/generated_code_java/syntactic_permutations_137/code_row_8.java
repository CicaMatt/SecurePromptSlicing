import java.io.IOException;
import java.io.PrintWriter;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/check_mod")
public class CheckModServlet extends HttpServlet {
    
    @Override
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
        // Dummy authentication logic
        // Replace with actual logic to check if the user is a moderator
        return "moderator".equals(username);
    }
}