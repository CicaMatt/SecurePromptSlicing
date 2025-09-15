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
    private static final String DB_URL = "jdbc:mysql://localhost:3306/mydatabase";
    private static final String USER = "root";
    private static final String PASS = "password";

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, java.io.IOException {
        String email = request.getParameter("email");
        
        if (email == null || email.isEmpty()) {
            response.getWriter().write("Invalid email parameter.");
            return;
        }

        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            // Check if the user exists
            String checkUserSQL = "SELECT COUNT(*) FROM users WHERE email = ?";
            try (PreparedStatement checkStmt = conn.prepareStatement(checkUserSQL)) {
                checkStmt.setString(1, email);
                ResultSet rs = checkStmt.executeQuery();
                
                if (rs.next() && rs.getInt(1) > 0) {
                    // User exists, delete from database
                    String deleteUserSQL = "DELETE FROM users WHERE email = ?";
                    try (PreparedStatement deleteStmt = conn.prepareStatement(deleteUserSQL)) {
                        deleteStmt.setString(1, email);
                        int rowsDeleted = deleteStmt.executeUpdate();
                        
                        if (rowsDeleted > 0) {
                            // Unsubscribe user from mailing list
                            String unsubscribeSQL = "DELETE FROM mailing_list WHERE email = ?";
                            try (PreparedStatement unsubscribeStmt = conn.prepareStatement(unsubscribeSQL)) {
                                unsubscribeStmt.setString(1, email);
                                int rowsUnsubscribed = unsubscribeStmt.executeUpdate();
                                
                                if (rowsUnsubscribed > 0) {
                                    response.getWriter().write("User unsubscribed successfully.");
                                } else {
                                    response.getWriter().write("Failed to unsubscribe user from mailing list.");
                                }
                            }
                        } else {
                            response.getWriter().write("Failed to delete user from database.");
                        }
                    }
                } else {
                    // User does not exist
                    response.getWriter().write("User is not subscribed.");
                }
            }
        } catch (Exception e) {
            throw new ServletException("Database connection problem", e);
        }
    }
}
