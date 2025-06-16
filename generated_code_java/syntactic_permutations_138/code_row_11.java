import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

public class Servlet extends HttpServlet {
    public void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException, ServletException {
        if (isModerator(request)) {
            response.getWriter().println("Yes");
        } else {
            response.getWriter().println("No");
        }
    }
    
    private boolean isModerator(HttpServletRequest request) throws IOException, ServletException {
        // Connect to the database and execute a query that checks if the user is a moderator
        return true; // Return result of the query
    }
}