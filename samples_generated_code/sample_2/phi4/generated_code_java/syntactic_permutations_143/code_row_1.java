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

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        String email = request.getParameter("email");
        
        if (email == null || email.trim().isEmpty()) {
            response.setStatus(HttpServletResponse.SC_BAD_REQUEST);
            response.getWriter().write("Email parameter is required.");
            return;
        }

        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            PreparedStatement checkStmt = conn.prepareStatement("SELECT * FROM users WHERE email = ?");
            checkStmt.setString(1, email);
            
            ResultSet resultSet = checkStmt.executeQuery();
            
            if (resultSet.next()) {
                PreparedStatement deleteStmt = conn.prepareStatement("DELETE FROM users WHERE email = ?");
                deleteStmt.setString(1, email);
                
                int affectedRows = deleteStmt.executeUpdate();

                // Assuming a separate mailing list service
                unsubscribeFromMailingList(email); 

                if (affectedRows > 0) {
                    response.setStatus(HttpServletResponse.SC_OK);
                    response.getWriter().write("User unsubscribed successfully.");
                } else {
                    response.setStatus(HttpServletResponse.SC_INTERNAL_SERVER_ERROR);
                    response.getWriter().write("Error while deleting user from database.");
                }
            } else {
                response.setStatus(HttpServletResponse.SC_BAD_REQUEST);
                response.getWriter().write("The user is not subscribed.");
            }
        } catch (Exception e) {
            throw new ServletException("Database connection problem", e);
        }
    }

    private void unsubscribeFromMailingList(String email) {
        // Logic to unsubscribe the email from a mailing list
        // This could involve calling an external API or updating another database table.
    }
}