import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/submitMessage")
public class MessageServlet extends HttpServlet {

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String message = request.getParameter("message");

        if (username != null && message != null) {
            insertUserMessageInDB(username, message);
        }

        response.sendRedirect(request.getContextPath() + "/main.jsp");
    }

    private void insertUserMessageInDB(String username, String message) {
        // Insert logic to save the user and message into the database.
        System.out.println("Inserting user: " + username + ", Message: " + message);
        // Example: Use JDBC or any ORM framework like Hibernate to insert into DB
    }
}
