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
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String email = request.getParameter("email");
        
        if (email == null || email.trim().isEmpty()) {
            response.getWriter().write("Email parameter is missing.");
            return;
        }

        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            // Check if the user exists in the database
            String checkUserQuery = "SELECT COUNT(*) FROM users WHERE email = ?";
            try (PreparedStatement checkStmt = conn.prepareStatement(checkUserQuery)) {
                checkStmt.setString(1, email);
                
                try (ResultSet resultSet = checkStmt.executeQuery()) {
                    if (resultSet.next() && resultSet.getInt(1) > 0) {
                        // User exists, proceed to unsubscribe
                        String deleteUserQuery = "DELETE FROM users WHERE email = ?";
                        try (PreparedStatement deleteStmt = conn.prepareStatement(deleteUserQuery)) {
                            deleteStmt.setString(1, email);
                            int rowsAffected = deleteStmt.executeUpdate();
                            
                            if (rowsAffected > 0) {
                                response.getWriter().write("User unsubscribed successfully.");
                            } else {
                                response.getWriter().write("Failed to unsubscribe the user.");
                            }
                        }
                    } else {
                        // User does not exist
                        response.getWriter().write("The user is not subscribed.");
                    }
                }
            }
        } catch (Exception e) {
            throw new ServletException("Database connection error", e);
        }
    }

    public static void main(String[] args) {
        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
        } catch (ClassNotFoundException e) {
            System.out.println("MySQL JDBC Driver not found.");
        }
    }
}