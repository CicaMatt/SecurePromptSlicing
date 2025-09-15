import java.io.IOException;
import java.util.HashMap;
import java.util.Map;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

@WebServlet("/changeEmail")
public class ChangeEmailServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;
    
    // Simulated database storage
    private Map<String, String> userDatabase = new HashMap<>();

    public void init() throws ServletException {
        super.init();
        // Pre-populating with a sample user for demonstration
        userDatabase.put("user@example.com", "password123");
    }

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        HttpSession session = request.getSession(false);

        if (session == null || session.getAttribute("loggedInUserEmail") == null) {
            response.sendRedirect("login.html");
            return;
        }

        String oldEmail = request.getParameter("oldEmail");
        String newEmail = request.getParameter("newEmail");
        String confirmPassword = request.getParameter("confirmPassword");

        String loggedInUserEmail = (String) session.getAttribute("loggedInUserEmail");

        if (!loggedInUserEmail.equals(oldEmail)) {
            response.getWriter().println("Old email does not match the logged in user.");
            return;
        }

        if (!userDatabase.containsKey(oldEmail)) {
            response.getWriter().println("The old email provided does not exist.");
            return;
        }

        String storedPassword = userDatabase.get(oldEmail);

        if (!storedPassword.equals(confirmPassword)) {
            response.getWriter().println("Incorrect password.");
            return;
        }

        if (newEmail == null || newEmail.isEmpty()) {
            response.getWriter().println("New email cannot be empty.");
            return;
        }

        if (userDatabase.containsKey(newEmail)) {
            response.getWriter().println("The new email is already in use.");
            return;
        }

        userDatabase.remove(oldEmail);
        userDatabase.put(newEmail, storedPassword);

        session.setAttribute("loggedInUserEmail", newEmail);

        response.getWriter().println("Email updated successfully!");
    }
}
