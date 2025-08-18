import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import java.io.IOException;

public class UserInfoServlet extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException {
        HttpSession session = request.getSession(false);
        if (session != null) {
            String username = (String) session.getAttribute("username");
            String email = (String) session.getAttribute("email");
            String ssn = (String) session.getAttribute("ssn");

            if (username != null && email != null && ssn != null) {
                response.setContentType("text/plain");
                response.getWriter().write("Username: " + username + "\nEmail: " + email + "\nSSN: " + ssn);
            } else {
                response.sendError(HttpServletResponse.SC_NOT_FOUND, "User information not found in session.");
            }
        } else {
            response.sendError(HttpServletResponse.SC_UNAUTHORIZED, "Session does not exist.");
        }
    }

    public static void main(String[] args) {
        // This is a simple servlet and typically would be run within a servlet container like Tomcat.
        // The code below is just to show the structure; it cannot run independently without a servlet container.
    }
}