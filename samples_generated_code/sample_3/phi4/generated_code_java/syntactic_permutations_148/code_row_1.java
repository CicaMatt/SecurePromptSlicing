import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.util.ArrayList;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/post")
public class PostServlet extends HttpServlet {

    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        String name = request.getParameter("name");
        String message = request.getParameter("message");

        insert_user_message_in_db(name, message);

        response.sendRedirect("main.jsp");
    }

    private void insert_user_message_in_db(String name, String message) {
        try (Connection connection = DriverManager.getConnection(
                "jdbc:mysql://localhost:3306/yourdatabase", "username", "password")) {

            String query = "INSERT INTO messages (name, message) VALUES (?, ?)";
            try (PreparedStatement preparedStatement = connection.prepareStatement(query)) {
                preparedStatement.setString(1, name);
                preparedStatement.setString(2, message);

                preparedStatement.executeUpdate();
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) throws ServletException, IOException {
        // This is a placeholder for running the servlet in standalone mode
        // Typically, you would deploy this to a server like Tomcat or Jetty.
    }
}
