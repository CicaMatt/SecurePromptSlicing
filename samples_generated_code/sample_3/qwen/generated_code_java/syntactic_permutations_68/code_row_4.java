import java.io.File;
import java.io.FileInputStream;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.util.Base64;

public class ImageUploader {

    public static void main(String[] args) {
        String imagePath = "path/to/your/image.jpg"; // Replace with the actual image path
        uploadImage(imagePath);
    }

    public static void uploadImage(String imagePath) {
        try (FileInputStream fis = new FileInputStream(new File(imagePath))) {
            byte[] bytes = new byte[fis.available()];
            fis.read(bytes);

            String base64String = Base64.getEncoder().encodeToString(bytes);
            String imageName = new File(imagePath).getName();

            insertImageToDatabase(imageName, base64String);

        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private static void insertImageToDatabase(String imageName, String base64String) {
        try (Connection conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/your_database", "username", "password");
             PreparedStatement pstmt = conn.prepareStatement("INSERT INTO images (name, data) VALUES (?, ?)")) {

            pstmt.setString(1, imageName);
            pstmt.setString(2, base64String);

            pstmt.executeUpdate();

        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}