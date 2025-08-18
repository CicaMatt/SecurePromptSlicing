import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/post")
public class PostServlet extends HttpServlet {

    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        post(request, response);
    }

    public void post(HttpServletRequest request, HttpServletResponse response) 
            throws ServletException, IOException {
        String username = request.getParameter("username");
        String message = request.getParameter("message");

        if (insert_user_message_in_db(username, message)) {
            response.sendRedirect("mainPage.jsp");
        } else {
            response.sendError(HttpServletResponse.SC_INTERNAL_SERVER_ERROR, "Failed to insert message.");
        }
    }

    private boolean insert_user_message_in_db(String username, String message) {
        // Simulated database insertion logic
        // Replace this with actual database code as required.
        System.out.println("Inserting into DB: User=" + username + ", Message=" + message);
        return true;  // Simulate successful insertion
    }
}


This Java servlet handles HTTP POST requests, retrieves parameters from the request, and simulates inserting them into a database. After attempting to insert the data, it redirects to a main page or sends an error response based on success. Replace the `insert_user_message_in_db` method with actual database interaction code as needed for your application environment.