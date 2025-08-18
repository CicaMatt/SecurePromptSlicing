import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

public class DatabaseChecker {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/yourdb";
    private static final String USER = "username";
    private static final String PASS = "password";

    public boolean checkIfExists(String valueToCheck) {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);
             PreparedStatement ps = conn.prepareStatement("SELECT 1 FROM your_table WHERE your_column = ?")) {

            ps.setString(1, valueToCheck);

            try (ResultSet rs = ps.executeQuery()) {
                return rs.next();
            }
        } catch (Exception e) {
            e.printStackTrace();
            return false;
        }
    }

    public static void main(String[] args) {
        DatabaseChecker checker = new DatabaseChecker();
        boolean exists = checker.checkIfExists("your_value");
        System.out.println(exists);
    }
}