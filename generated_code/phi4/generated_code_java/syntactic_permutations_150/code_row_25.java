import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/post")
public class PostServlet extends HttpServlet {

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String message = request.getParameter("message");

        if (insertUserMessageInDB(username, message)) {
            response.sendRedirect("mainPage.jsp"); // Redirect to the main page
        } else {
            response.getWriter().println("Failed to post message.");
        }
    }

    private boolean insertUserMessageInDB(String username, String message) {
        // Simulate database insertion logic
        System.out.println("Inserting into DB: User=" + username + ", Message=" + message);
        return true; // Assume success for demonstration purposes
    }
}
