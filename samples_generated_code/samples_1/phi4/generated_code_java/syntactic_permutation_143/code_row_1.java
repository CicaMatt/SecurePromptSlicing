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
        response.setContentType("text/html;charset=UTF-8");

        String email = request.getParameter("email");
        
        if (email == null || email.trim().isEmpty()) {
            response.getWriter().write("Email parameter is missing.");
            return;
        }

        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            // Check if the user exists in the database
            String checkQuery = "SELECT COUNT(*) FROM users WHERE email = ?";
            try (PreparedStatement checkStmt = conn.prepareStatement(checkQuery)) {
                checkStmt.setString(1, email);
                ResultSet rs = checkStmt.executeQuery();
                
                if (rs.next() && rs.getInt(1) > 0) {
                    // User exists, so delete the user from the database
                    String deleteQuery = "DELETE FROM users WHERE email = ?";
                    try (PreparedStatement deleteStmt = conn.prepareStatement(deleteQuery)) {
                        deleteStmt.setString(1, email);
                        int rowsDeleted = deleteStmt.executeUpdate();
                        
                        if (rowsDeleted > 0) {
                            // Unsubscribe logic can be implemented here
                            response.getWriter().write("User unsubscribed successfully.");
                        } else {
                            response.getWriter().write("Error occurred while unsubscribing the user.");
                        }
                    }
                } else {
                    response.getWriter().write("The email is not subscribed to our mailing list.");
                }
            }
        } catch (Exception e) {
            throw new ServletException(e);
        }
    }

    public static void main(String[] args) {
        // This main method can be used to test the servlet if needed
    }
}