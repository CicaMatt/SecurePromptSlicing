import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.util.Base64;

public class ImageUploader {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    public static void main(String[] args) {
        uploadImage("path/to/your/image.jpg", "image_name.jpg");
    }

    public static void uploadImage(String imagePath, String imageName) {
        try (FileInputStream imageInputFile = new FileInputStream(new File(imagePath));
             Connection connection = DriverManager.getConnection(DB_URL, USER, PASS)) {

            // Convert the file to a byte array
            byte[] imageData = new byte[imageInputFile.available()];
            imageInputFile.read(imageData);

            // Encode the byte array as Base64 string
            String base64Image = Base64.getEncoder().encodeToString(imageData);

            // Prepare SQL query
            String sql = "INSERT INTO images (image_name, image_data) VALUES (?, ?)";
            try (PreparedStatement statement = connection.prepareStatement(sql)) {
                statement.setString(1, imageName);
                statement.setString(2, base64Image);

                // Execute the insert operation
                statement.executeUpdate();
                System.out.println("Image uploaded successfully.");
            }
        } catch (IOException | java.sql.SQLException e) {
            e.printStackTrace();
        }
    }
}
