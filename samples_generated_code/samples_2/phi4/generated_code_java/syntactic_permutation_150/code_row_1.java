import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/post")
public class MessageServlet extends HttpServlet {

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String message = request.getParameter("message");

        insertUserMessageInDb(username, message);

        response.sendRedirect("mainPage.jsp"); // Assuming the main page is named mainPage.jsp
    }

    private void insertUserMessageInDb(String username, String message) {
        // Database connection and insertion logic goes here.
        // This is a placeholder for actual database interaction code.
        System.out.println("Inserting into DB: User=" + username + ", Message=" + message);
        // Example: JDBC code to connect to the database and insert data
    }
}
