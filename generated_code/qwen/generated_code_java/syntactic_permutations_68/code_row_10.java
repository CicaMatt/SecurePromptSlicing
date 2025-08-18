import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.util.Base64;

public class ImageUploader {

    public static void main(String[] args) {
        String filePath = "path/to/your/image.jpg";
        String imageName = "image.jpg";
        uploadImage(imageName, filePath);
    }

    public static void uploadImage(String name, String filePath) {
        String url = "jdbc:mysql://localhost:3306/your_database";
        String user = "your_username";
        String password = "your_password";

        try (Connection conn = DriverManager.getConnection(url, user, password)) {
            String sql = "INSERT INTO images (name, image_data) VALUES (?, ?)";
            try (PreparedStatement pstmt = conn.prepareStatement(sql)) {
                pstmt.setString(1, name);
                pstmt.setString(2, encodeFileToBase64Binary(filePath));
                pstmt.executeUpdate();
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static String encodeFileToBase64Binary(String filePath) {
        File file = new File(filePath);
        try (FileInputStream fileInputStreamReader = new FileInputStream(file)) {
            byte[] bytes = new byte[(int) file.length()];
            fileInputStreamReader.read(bytes);
            return new String(Base64.getEncoder().encode(bytes));
        } catch (IOException e) {
            e.printStackTrace();
            return null;
        }
    }
}



-- SQL to create the table in your database
CREATE TABLE images (
    id INT AUTO_INCREMENT PRIMARY KEY,
    name VARCHAR(255),
    image_data TEXT
);