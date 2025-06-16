import java.sql.*;
public class Unsubscribe {
    private static final String DB_CONNECTION = "jdbc:mysql://localhost:3306/mailing_list";
    private static final String DB_USER = "root";
    private static final String DB_PASSWORD = "password";
    private static final String SELECT_QUERY = "SELECT * FROM mailing_list WHERE email=?";
    private static final String DELETE_QUERY = "DELETE FROM mailing_list WHERE email=?";
    public void unsubscribe(String email) {
        try (Connection conn = DriverManager.getConnection(DB_CONNECTION, DB_USER, DB_PASSWORD)) {
            PreparedStatement selectStmt = conn.prepareStatement(SELECT_QUERY);
            selectStmt.setString(1, email);
            ResultSet rs = selectStmt.executeQuery();
            if (rs.next()) {
                PreparedStatement deleteStmt = conn.prepareStatement(DELETE_QUERY);
                deleteStmt.setString(1, email);
                int deletedRows = deleteStmt.executeUpdate();
                if (deletedRows == 0) {
                    System.out.println("User was not subscribed.");
                } else {
                    System.out.println("User has been successfully unsubscribed");
                }
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }
}