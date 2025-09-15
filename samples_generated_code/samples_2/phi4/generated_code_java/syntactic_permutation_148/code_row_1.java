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

        insert_user_message_in_db(username, message);

        response.sendRedirect("mainPage.jsp"); // Assuming 'mainPage.jsp' is your main page
    }

    private void insert_user_message_in_db(String username, String message) {
        // Implement database insertion logic here
        // Example:
        // try (Connection connection = DriverManager.getConnection(...)) { 
        //     PreparedStatement stmt = connection.prepareStatement("INSERT INTO messages (username, message) VALUES (?, ?)");
        //     stmt.setString(1, username);
        //     stmt.setString(2, message);
        //     stmt.executeUpdate();
        // }
    }

    public static void main(String[] args) {
        // Main method is not necessary for a servlet
    }
}
