import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/unsubscribe")
public class UnsubscribeServlet extends HttpServlet {
    
    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "root";
    private static final String PASSWORD = "password";

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws Exception {
        String email = request.getParameter("email");
        
        if (email == null || email.isEmpty()) {
            response.setStatus(HttpServletResponse.SC_BAD_REQUEST);
            response.getWriter().write("Email parameter is missing.");
            return;
        }

        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASSWORD)) {
            String query = "SELECT COUNT(*) FROM users WHERE email = ?";
            
            try (PreparedStatement stmt = conn.prepareStatement(query)) {
                stmt.setString(1, email);
                try (ResultSet rs = stmt.executeQuery()) {
                    if (rs.next() && rs.getInt(1) > 0) {
                        deleteAndUnsubscribeUser(conn, email);
                        response.getWriter().write("Successfully unsubscribed.");
                    } else {
                        response.getWriter().write("The user is not subscribed.");
                    }
                }
            }
        } catch (SQLException e) {
            throw new RuntimeException("Database error", e);
        }
    }

    private void deleteAndUnsubscribeUser(Connection conn, String email) throws SQLException {
        String deleteUserQuery = "DELETE FROM users WHERE email = ?";
        try (PreparedStatement stmt = conn.prepareStatement(deleteUserQuery)) {
            stmt.setString(1, email);
            stmt.executeUpdate();
        }
        
        // Assuming a separate mailing list table
        String unsubscribeFromMailingListQuery = "DELETE FROM mailing_list WHERE email = ?";
        try (PreparedStatement stmt = conn.prepareStatement(unsubscribeFromMailingListQuery)) {
            stmt.setString(1, email);
            stmt.executeUpdate();
        }
    }

    public void init() throws ServletException {
        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
        } catch (ClassNotFoundException e) {
            throw new ServletException("MySQL JDBC driver not found", e);
        }
    }
}