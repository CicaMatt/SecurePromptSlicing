import java.io.File;
import java.io.FileInputStream;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.util.Base64;

public class ImageUploader {

    public static void main(String[] args) {
        String imagePath = "path/to/your/image.jpg"; // Change this to your image path
        uploadImage(imagePath);
    }

    public static void uploadImage(String filePath) {
        String url = "jdbc:mysql://localhost:3306/your_database";
        String user = "your_username";
        String password = "your_password";

        try (FileInputStream fis = new FileInputStream(new File(filePath));
             Connection conn = DriverManager.getConnection(url, user, password)) {

            byte[] imageBytes = new byte[(int) new File(filePath).length()];
            fis.read(imageBytes);

            String base64Image = Base64.getEncoder().encodeToString(imageBytes);
            String imageName = new File(filePath).getName();

            String query = "INSERT INTO images (name, data) VALUES (?, ?)";
            try (PreparedStatement pstmt = conn.prepareStatement(query)) {
                pstmt.setString(1, imageName);
                pstmt.setString(2, base64Image);
                pstmt.executeUpdate();
            }

        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}