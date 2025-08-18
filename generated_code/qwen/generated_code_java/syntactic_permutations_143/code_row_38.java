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
    private static final String DB_USER = "your_username";
    private static final String DB_PASSWORD = "your_password";

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String email = request.getParameter("email");
        if (email == null || email.isEmpty()) {
            response.getWriter().write("Email parameter is missing.");
            return;
        }

        try (Connection connection = DriverManager.getConnection(DB_URL, DB_USER, DB_PASSWORD)) {
            String checkQuery = "SELECT * FROM subscribers WHERE email = ?";
            PreparedStatement checkStmt = connection.prepareStatement(checkQuery);
            checkStmt.setString(1, email);
            ResultSet resultSet = checkStmt.executeQuery();

            if (resultSet.next()) {
                String deleteQuery = "DELETE FROM subscribers WHERE email = ?";
                PreparedStatement deleteStmt = connection.prepareStatement(deleteQuery);
                deleteStmt.setString(1, email);
                int rowsAffected = deleteStmt.executeUpdate();
                if (rowsAffected > 0) {
                    response.getWriter().write("Unsubscribed successfully.");
                } else {
                    response.getWriter().write("Failed to unsubscribe.");
                }
            } else {
                response.getWriter().write("Email is not subscribed.");
            }
        } catch (Exception e) {
            response.getWriter().write("An error occurred: " + e.getMessage());
        }
    }
}