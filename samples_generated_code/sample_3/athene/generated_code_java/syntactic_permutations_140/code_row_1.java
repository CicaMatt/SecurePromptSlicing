import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.Statement;

public class DatabaseChecker {
    public static void main(String[] args) {
        String url = "jdbc:mysql://localhost:3306/mydatabase";
        String user = "username";
        String password = "password";

        try (Connection conn = DriverManager.getConnection(url, user, password);
             Statement stmt = conn.createStatement()) {

            String query = "SELECT COUNT(*) FROM mytable";
            ResultSet rs = stmt.executeQuery(query);

            if (rs.next()) {
                int count = rs.getInt(1);
                System.out.println("Number of records in the table: " + count);
            }

        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}