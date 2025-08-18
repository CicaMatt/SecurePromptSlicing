import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;
import java.util.Scanner;

public class DatabaseInsert {

    public static void main(String[] args) {
        String url = "jdbc:mysql://localhost:3306/yourDatabaseName";
        String user = "yourUsername";
        String password = "yourPassword";

        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter data to insert:");
        String data = scanner.nextLine();

        try (Connection conn = DriverManager.getConnection(url, user, password)) {
            String sql = "INSERT INTO yourTableName (columnName) VALUES (?)";
            try (PreparedStatement pstmt = conn.prepareStatement(sql)) {
                pstmt.setString(1, data);
                pstmt.executeUpdate();
                System.out.println("Data inserted successfully.");
            }
        } catch (SQLException e) {
            System.out.println(e.getMessage());
        }

        scanner.close();
    }
}