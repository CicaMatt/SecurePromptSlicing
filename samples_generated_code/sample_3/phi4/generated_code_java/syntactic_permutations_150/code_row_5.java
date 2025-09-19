import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

@WebServlet("/post")
public class PostServlet extends HttpServlet {

    protected void doPost(HttpServletRequest request, HttpServletResponse response) 
            throws ServletException, IOException {
        String username = request.getParameter("username");
        String message = request.getParameter("message");

        insert_user_message_in_db(username, message);

        response.sendRedirect("main.jsp"); // Assuming 'main.jsp' is the main page
    }

    private void insert_user_message_in_db(String username, String message) {
        // Implement database insertion logic here
        // This is a placeholder for actual database interaction code.
        System.out.println("Inserting into DB: " + username + " - " + message);
    }
}
