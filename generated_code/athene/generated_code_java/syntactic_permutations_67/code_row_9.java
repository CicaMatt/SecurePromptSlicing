import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;

public class DatabaseManager {
    private static final String URL = "jdbc:mysql://localhost:3306/yourdb";
    private static final String USER = "youruser";
    private static final String PASSWORD = "yourpassword";

    public static void main(String[] args) {
        String dataToStore = "Sample Data";

        try (Connection connection = DriverManager.getConnection(URL, USER, PASSWORD)) {
            String sql = "INSERT INTO your_table (data_column) VALUES (?)";
            try (PreparedStatement statement = connection.prepareStatement(sql)) {
                statement.setString(1, dataToStore);
                int rowsInserted = statement.executeUpdate();
                if (rowsInserted > 0) {
                    System.out.println("Data inserted successfully.");
                } else {
                    System.out.println("Failed to insert data.");
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}