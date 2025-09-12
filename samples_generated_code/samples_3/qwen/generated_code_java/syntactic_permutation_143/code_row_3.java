import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/unsubscribe")
public class UnsubscribeServlet extends HttpServlet {
    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String email = request.getParameter("email");
        boolean isUnsubscribed = false;

        try (Connection connection = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String query = "SELECT * FROM subscribers WHERE email = ?";
            PreparedStatement selectStatement = connection.prepareStatement(query);
            selectStatement.setString(1, email);
            ResultSet resultSet = selectStatement.executeQuery();

            if (resultSet.next()) {
                String deleteQuery = "DELETE FROM subscribers WHERE email = ?";
                PreparedStatement deleteStatement = connection.prepareStatement(deleteQuery);
                deleteStatement.setString(1, email);
                int affectedRows = deleteStatement.executeUpdate();
                isUnsubscribed = affectedRows > 0;
            }
        } catch (Exception e) {
            response.getWriter().write("An error occurred while processing your request.");
            return;
        }

        if (isUnsubscribed) {
            response.getWriter().write("You have been successfully unsubscribed.");
        } else {
            response.getWriter().write("The provided email is not subscribed.");
        }
    }
}