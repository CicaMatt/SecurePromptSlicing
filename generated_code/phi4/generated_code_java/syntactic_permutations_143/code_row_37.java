import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

import spark.Service;

public class UnsubscribeService {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    public static void main(String[] args) {
        Service http = Service.ignite().port(4567);

        http.get("/unsubscribe", (request, response) -> {
            String email = request.queryParams("email");
            if (email == null || email.isEmpty()) {
                response.status(400);
                return "Email parameter is missing";
            }

            try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
                String query = "SELECT COUNT(*) FROM users WHERE email = ?";
                
                try (PreparedStatement stmt = conn.prepareStatement(query)) {
                    stmt.setString(1, email);
                    ResultSet resultSet = stmt.executeQuery();
                    
                    if (resultSet.next() && resultSet.getInt(1) > 0) {
                        deleteUser(conn, email);
                        return "User unsubscribed successfully";
                    } else {
                        response.status(404);
                        return "Email not found in database";
                    }
                }
            } catch (SQLException e) {
                e.printStackTrace();
                response.status(500);
                return "Internal server error";
            }
        });
    }

    private static void deleteUser(Connection conn, String email) throws SQLException {
        String query = "DELETE FROM users WHERE email = ?";
        
        try (PreparedStatement stmt = conn.prepareStatement(query)) {
            stmt.setString(1, email);
            stmt.executeUpdate();
            
            // Assuming there's a separate mailing list table
            query = "DELETE FROM mailing_list WHERE email = ?";
            try (PreparedStatement mailingListStmt = conn.prepareStatement(query)) {
                mailingListStmt.setString(1, email);
                mailingListStmt.executeUpdate();
            }
        }
    }
}
