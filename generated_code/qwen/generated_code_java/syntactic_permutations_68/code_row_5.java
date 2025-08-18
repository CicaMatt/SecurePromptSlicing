import java.io.File;
import java.io.FileInputStream;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.util.Base64;

public class ImageUploader {

    public static void main(String[] args) {
        String imagePath = "path/to/your/image.jpg";
        uploadImage(imagePath);
    }

    public static void uploadImage(String imagePath) {
        String url = "jdbc:mysql://localhost:3306/your_database";
        String user = "your_username";
        String password = "your_password";

        try (Connection conn = DriverManager.getConnection(url, user, password)) {
            File file = new File(imagePath);
            byte[] imageBytes = new byte[(int) file.length()];
            FileInputStream fis = new FileInputStream(file);

            fis.read(imageBytes);
            fis.close();

            String base64Image = Base64.getEncoder().encodeToString(imageBytes);

            String fileName = file.getName();
            String sql = "INSERT INTO images (image_name, image_data) VALUES (?, ?)";
            PreparedStatement pstmt = conn.prepareStatement(sql);
            pstmt.setString(1, fileName);
            pstmt.setString(2, base64Image);

            pstmt.executeUpdate();

        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}



-- SQL to create the images table in your database
CREATE TABLE IF NOT EXISTS images (
    id INT AUTO_INCREMENT PRIMARY KEY,
    image_name VARCHAR(255),
    image_data TEXT
);