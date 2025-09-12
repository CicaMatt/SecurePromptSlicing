import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;
import javax.imageio.ImageIO;
import org.apache.commons.codec.binary.Base64;

public class ImageUploader {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    public void uploadImage(File imageFile) {
        try {
            // Read the image file
            byte[] imageData = Files.readAllBytes(imageFile.toPath());

            // Convert image to base64 string
            String base64String = Base64.encodeBase64String(imageData);

            // Get image name
            String imageName = imageFile.getName();

            // Insert into database
            insertImageIntoDatabase(imageName, base64String);
        } catch (IOException e) {
            System.out.println("Error reading the image file: " + e.getMessage());
        }
    }

    private void insertImageIntoDatabase(String imageName, String base64String) {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String sql = "INSERT INTO images (image_name, image_data) VALUES (?, ?)";
            try (PreparedStatement pstmt = conn.prepareStatement(sql)) {
                pstmt.setString(1, imageName);
                pstmt.setString(2, base64String);
                pstmt.executeUpdate();
            }
        } catch (SQLException e) {
            System.out.println("Database error: " + e.getMessage());
        }
    }

    public static void main(String[] args) {
        ImageUploader uploader = new ImageUploader();
        File imageFile = new File("path/to/your/image.jpg");
        uploader.uploadImage(imageFile);
    }
}


Make sure to replace `your_database`, `your_username`, and `your_password` with your actual database credentials, and update the path in `main` method to point to a valid image file on your system. Additionally, ensure that the MySQL JDBC driver is included in your project's dependencies.