import java.io.IOException;
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
        
        boolean isModerator = auth_mod();

        if (isModerator) {
            response.getWriter().write("User is a moderator.");
        } else {
            response.getWriter().write("User is not a moderator.");
        }
    }

    private boolean auth_mod() {
        // Logic to determine if the user is a moderator.
        // For demonstration purposes, let's return true or false randomly
        // In a real-world application, this could be based on session attributes or database checks

        return Math.random() > 0.5; // Example logic: Randomly returns true or false
    }
}