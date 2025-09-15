import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/SubmitMessage")
public class SubmitMessageServlet extends HttpServlet {

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String message = request.getParameter("message");

        insert_user_message_in_db(username, message);

        response.sendRedirect("mainPage.jsp"); // Assuming the main page is 'mainPage.jsp'
    }

    private void insert_user_message_in_db(String username, String message) {
        // Code to insert user and message into database
        // This can be implemented using JDBC or any ORM framework like Hibernate
        System.out.println("Inserting into DB: Username = " + username + ", Message = " + message);
        // Example placeholder for actual implementation
    }
}
