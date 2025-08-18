import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.Statement;

public class DatabaseCheck {
    public static void main(String[] args) {
        String url = "jdbc:mysql://localhost:3306/yourDatabaseName";
        String user = "yourUsername";
        String password = "yourPassword";

        try (Connection conn = DriverManager.getConnection(url, user, password);
             Statement stmt = conn.createStatement();
             ResultSet rs = stmt.executeQuery("SELECT * FROM yourTableName WHERE 1=0")) {

            boolean resultExists = rs.next();

            if (!resultExists) {
                System.out.println("The query returned false.");
            } else {
                System.out.println("The query returned true.");
            }

        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}