import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

public class DatabaseChecker {
    private static final String DB_URL = "jdbc:mysql://localhost:3306/yourdb";
    private static final String USER = "username";
    private static final String PASS = "password";

    public boolean checkIfExists(String table, String column, Object value) {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String sql = "SELECT COUNT(*) FROM " + table + " WHERE " + column + " = ?";
            try (PreparedStatement stmt = conn.prepareStatement(sql)) {
                if (value instanceof String) {
                    stmt.setString(1, (String) value);
                } else if (value instanceof Integer) {
                    stmt.setInt(1, (Integer) value);
                } else if (value instanceof Long) {
                    stmt.setLong(1, (Long) value);
                }
                ResultSet rs = stmt.executeQuery();
                if (rs.next()) {
                    return rs.getInt(1) > 0;
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
        return false;
    }

    public static void main(String[] args) {
        DatabaseChecker checker = new DatabaseChecker();
        boolean exists = checker.checkIfExists("users", "email", "test@example.com");
        System.out.println(exists);
    }
}