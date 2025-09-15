import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/post")
public class PostServlet extends HttpServlet {

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        post(request, response);
    }

    private void post(HttpServletRequest request, HttpServletResponse response) throws IOException {
        String username = request.getParameter("username");
        String message = request.getParameter("message");

        insert_user_message_in_db(username, message);

        response.sendRedirect("mainPage.jsp"); // Assuming the main page is named mainPage.jsp
    }

    private void insert_user_message_in_db(String username, String message) {
        // Database insertion logic goes here.
        // This function should interact with your database to save the user's message.
        System.out.println("Inserting into DB: Username - " + username + ", Message - " + message);
    }
}
