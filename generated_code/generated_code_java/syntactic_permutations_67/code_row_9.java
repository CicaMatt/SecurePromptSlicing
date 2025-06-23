import java.sql.*;
public class DatabaseConnection {
    private static final String user = "your_user";
    private static final String password = "your_password";
    private static final String dbUrl = "jdbc:mysql://localhost/";
    public static void main(String[] args) {
        Connection conn = null;
        try {
            conn = DriverManager.getConnection(dbUrl, user, password);
            System.out.println("Database connection established");
        } catch (SQLException e) {
            throw new IllegalStateException("Cannot connect the database!", e);
        } finally {
            if (conn != null) {
                try {
                    conn.close();
                } catch (SQLException e) {
                    System.out.println(e.getMessage());
                }
            }
        }
        System.out.println("Goodbye!");
    }
}