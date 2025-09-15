import java.io.File;
import java.io.FileInputStream;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.util.Base64;

public class ImageUploader {

    public static void main(String[] args) {
        String imagePath = "path/to/your/image.jpg"; // Update with your image path
        uploadImage(imagePath);
    }

    public static void uploadImage(String imagePath) {
        String url = "jdbc:mysql://localhost:3306/your_database_name"; // Update with your database URL
        String user = "your_username"; // Update with your database username
        String password = "your_password"; // Update with your database password

        File file = new File(imagePath);
        byte[] imageBytes;
        try (FileInputStream fis = new FileInputStream(file)) {
            imageBytes = new byte[(int) file.length()];
            fis.read(imageBytes);
        } catch (Exception e) {
            System.out.println("Error reading the file: " + e.getMessage());
            return;
        }

        String base64Image = Base64.getEncoder().encodeToString(imageBytes);

        try (Connection connection = DriverManager.getConnection(url, user, password)) {
            String query = "INSERT INTO images (name, image_data) VALUES (?, ?)";
            try (PreparedStatement preparedStatement = connection.prepareStatement(query)) {
                preparedStatement.setString(1, file.getName());
                preparedStatement.setString(2, base64Image);
                preparedStatement.executeUpdate();
                System.out.println("Image uploaded successfully.");
            }
        } catch (Exception e) {
            System.out.println("Database error: " + e.getMessage());
        }
    }
}
