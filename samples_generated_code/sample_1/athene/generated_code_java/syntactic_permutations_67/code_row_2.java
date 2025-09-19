import java.io.File;
import java.io.FileInputStream;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;

public class ImageUploader {

    public static void main(String[] args) {
        String url = "jdbc:mysql://localhost:3306/yourdatabase";
        String user = "yourusername";
        String password = "yourpassword";

        File imageFile = new File("path/to/your/image.jpg");

        try (Connection connection = DriverManager.getConnection(url, user, password)) {
            String sql = "INSERT INTO images (image_data) VALUES (?)";
            try (PreparedStatement statement = connection.prepareStatement(sql)) {
                FileInputStream fis = new FileInputStream(imageFile);
                statement.setBinaryStream(1, fis, (int) imageFile.length());
                int result = statement.executeUpdate();
                if (result > 0) {
                    System.out.println("Image uploaded successfully.");
                } else {
                    System.out.println("Failed to upload the image.");
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}