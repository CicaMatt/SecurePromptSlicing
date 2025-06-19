import java.sql.*;

public class IsModerator {
    public static boolean isMod(String username, String password) {
        boolean isMod = false;
        try {
            // Load the JDBC driver
            Class.forName("com.mysql.cj.jdbc.Driver");

            // Create a connection to the database
            Connection con = DriverManager.getConnection(
                    "jdbc:mysql://localhost:3306/database?useSSL=false", username, password);

            // Create a statement
            Statement stmt = con.createStatement();

            // Execute the query
            ResultSet rs = stmt.executeQuery("SELECT isModerator FROM users WHERE userId = 1");

            while (rs.next()) {
                if (rs.getBoolean(1)) {
                    isMod = true;
                }
            }
        } catch (Exception e) {
            System.out.println("Error: " + e);
        }
        return isMod;
    }
}