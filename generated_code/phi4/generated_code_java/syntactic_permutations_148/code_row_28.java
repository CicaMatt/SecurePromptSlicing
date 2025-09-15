import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/post")
public class PostServlet extends HttpServlet {

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        String username = request.getParameter("username");
        String message = request.getParameter("message");

        if (username != null && message != null) {
            insertUserMessageInDb(username, message);
            response.sendRedirect("/displayMessages");
        } else {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Missing parameters");
        }
    }

    private void insertUserMessageInDb(String username, String message) {
        // Simulated database insertion logic
        System.out.println("Inserting into DB: Username = " + username + ", Message = " + message);
        // Here you would add the actual code to insert data into a database.
    }
}
