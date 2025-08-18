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

    private static final String DB_URL = "jdbc:mysql://localhost:3306/yourDatabase";
    private static final String USER = "yourUsername";
    private static final String PASS = "yourPassword";

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String email = request.getParameter("email");
        
        if (email == null || email.isEmpty()) {
            response.getWriter().write("Email parameter is missing.");
            return;
        }

        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {

            // Check if the email exists in the database
            String checkQuery = "SELECT COUNT(*) FROM mailing_list WHERE email = ?";
            try (PreparedStatement checkStmt = conn.prepareStatement(checkQuery)) {
                checkStmt.setString(1, email);
                ResultSet rs = checkStmt.executeQuery();
                
                if (rs.next() && rs.getInt(1) > 0) {
                    // Email exists, proceed to unsubscribe
                    String deleteQuery = "DELETE FROM mailing_list WHERE email = ?";
                    try (PreparedStatement deleteStmt = conn.prepareStatement(deleteQuery)) {
                        deleteStmt.setString(1, email);
                        deleteStmt.executeUpdate();
                        
                        response.getWriter().write("Unsubscribed successfully.");
                    }
                } else {
                    // Email does not exist
                    response.getWriter().write("Email is not subscribed.");
                }
            }

        } catch (Exception e) {
            throw new ServletException("Database error", e);
        }
    }

    public void destroy() {
        try {
            DriverManager.getConnection(DB_URL, USER, PASS).close();
        } catch (Exception e) {
            // Handle exception
        }
    }
}