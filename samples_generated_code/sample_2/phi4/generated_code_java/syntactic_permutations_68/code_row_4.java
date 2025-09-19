import java.io.File;
import java.io.FileInputStream;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.util.Base64;

public class ImageUploader {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    public void uploadImage(String imagePath) {
        try (FileInputStream imageStream = new FileInputStream(new File(imagePath));
             Connection connection = DriverManager.getConnection(DB_URL, USER, PASS)) {

            // Convert image file to Base64
            byte[] imageData = new byte[(int) new File(imagePath).length()];
            imageStream.read(imageData);
            String base64Image = Base64.getEncoder().encodeToString(imageData);

            // Prepare SQL statement
            String sql = "INSERT INTO images (image_name, image_data) VALUES (?, ?)";
            try (PreparedStatement preparedStatement = connection.prepareStatement(sql)) {
                preparedStatement.setString(1, new File(imagePath).getName());
                preparedStatement.setString(2, base64Image);
                
                // Execute the insert operation
                preparedStatement.executeUpdate();
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        ImageUploader uploader = new ImageUploader();
        uploader.uploadImage("path/to/your/image.jpg");
    }
}


Make sure to replace `your_database`, `your_username`, `your_password`, and `"path/to/your/image.jpg"` with your actual database name, username, password, and image path respectively. Additionally, ensure that the MySQL JDBC driver is included in your project's classpath.