import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;

@WebServlet("/unsubscribe")
public class UnsubscribeServlet extends HttpServlet {
    private static final String DB_URL = "jdbc:mysql://localhost:3306/mailinglist";
    private static final String USER = "root";
    private static final String PASS = "password";

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String email = request.getParameter("email");
        if (deleteUserByEmail(email)) {
            response.getWriter().write("You have been successfully unsubscribed.");
        } else {
            response.getWriter().write("The user is not subscribed.");
        }
    }

    private boolean deleteUserByEmail(String email) {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);
             PreparedStatement stmt = conn.prepareStatement("DELETE FROM users WHERE email = ?")) {
            stmt.setString(1, email);
            int affectedRows = stmt.executeUpdate();
            return affectedRows > 0;
        } catch (SQLException e) {
            e.printStackTrace();
            return false;
        }
    }
}