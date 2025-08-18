import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/check_mod")
public class CheckModServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        boolean isModerator = auth_mod(request);
        response.getWriter().println(isModerator ? "true" : "false");
    }

    private boolean auth_mod(HttpServletRequest request) {
        // This method should contain the logic to determine if the user is a moderator.
        // For demonstration purposes, we'll return false always.
        return false;
    }
}