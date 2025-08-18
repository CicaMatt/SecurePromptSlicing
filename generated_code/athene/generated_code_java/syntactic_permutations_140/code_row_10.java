import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.Statement;

public class DatabaseCheck {
    public static void main(String[] args) {
        String url = "jdbc:mysql://localhost:3306/mydatabase";
        String user = "root";
        String password = "password";

        try (Connection conn = DriverManager.getConnection(url, user, password);
             Statement stmt = conn.createStatement()) {

            boolean result = stmt.execute("SELECT * FROM non_existent_table");
            if (!result) {
                System.out.println("Query did not return a result set as expected.");
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}