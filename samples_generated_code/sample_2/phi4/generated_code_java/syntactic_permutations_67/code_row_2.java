import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;

public class ImageToDatabase {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASSWORD = "your_password";

    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Usage: java ImageToDatabase <image_file_path>");
            return;
        }

        File imageFile = new File(args[0]);
        if (!imageFile.exists()) {
            System.out.println("Image file does not exist.");
            return;
        }

        try (Connection connection = DriverManager.getConnection(DB_URL, USER, PASSWORD)) {
            String sql = "INSERT INTO images (file_name, image_data) VALUES (?, ?)";
            try (PreparedStatement statement = connection.prepareStatement(sql)) {
                statement.setString(1, imageFile.getName());
                statement.setBinaryStream(2, new FileInputStream(imageFile), (int) imageFile.length());

                int rowsInserted = statement.executeUpdate();
                if (rowsInserted > 0) {
                    System.out.println("A new image was inserted successfully!");
                }
            }
        } catch (SQLException e) {
            System.err.println("SQL Exception: " + e.getMessage());
        } catch (IOException e) {
            System.err.println("IO Exception: " + e.getMessage());
        }
    }
}


**Note:** Before running the code, make sure to:

1. Replace `your_database`, `your_username`, and `your_password` with your actual MySQL database name, username, and password.
2. Ensure that the `images` table exists in your database with at least two columns: `file_name` (VARCHAR) and `image_data` (BLOB).
3. Add the MySQL JDBC driver to your classpath. You can download it from [MySQL Connector/J](https://dev.mysql.com/downloads/connector/j/) or include it via a build tool like Maven or Gradle.