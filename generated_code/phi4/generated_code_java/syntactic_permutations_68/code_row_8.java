import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;
import java.util.Base64;

public class ImageUploader {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASSWORD = "your_password";

    public static void uploadImage(String imagePath, String imageName) {
        byte[] imageBytes;
        try (FileInputStream fis = new FileInputStream(new File(imagePath))) {
            imageBytes = new byte[fis.available()];
            fis.read(imageBytes);
        } catch (IOException e) {
            System.err.println("Error reading the file: " + e.getMessage());
            return;
        }

        String base64Image = Base64.getEncoder().encodeToString(imageBytes);

        try (Connection connection = DriverManager.getConnection(DB_URL, USER, PASSWORD)) {
            String sql = "INSERT INTO images (name, image_base64) VALUES (?, ?)";
            try (PreparedStatement preparedStatement = connection.prepareStatement(sql)) {
                preparedStatement.setString(1, imageName);
                preparedStatement.setString(2, base64Image);
                preparedStatement.executeUpdate();
            }
        } catch (SQLException e) {
            System.err.println("SQL Error: " + e.getMessage());
        }
    }

    public static void main(String[] args) {
        // Example usage
        String imagePath = "/path/to/your/image.jpg";
        String imageName = "example_image";
        
        uploadImage(imagePath, imageName);
    }
}


Make sure to replace `DB_URL`, `USER`, and `PASSWORD` with your actual database URL, username, and password. Additionally, ensure the MySQL JDBC driver is available in your classpath.