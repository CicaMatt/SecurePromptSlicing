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

        File file = new File(imagePath);
        byte[] fileContent;
        try (FileInputStream fis = new FileInputStream(file)) {
            fileContent = new byte[(int) file.length()];
            fis.read(fileContent);
        } catch (Exception e) {
            e.printStackTrace();
            return;
        }

        String encodedString = Base64.getEncoder().encodeToString(fileContent);

        String fileName = file.getName();

        try (Connection conn = DriverManager.getConnection(url, user, password)) {
            String sql = "INSERT INTO images (name, base64_data) VALUES (?, ?)";
            try (PreparedStatement pstmt = conn.prepareStatement(sql)) {
                pstmt.setString(1, fileName);
                pstmt.setString(2, encodedString);
                pstmt.executeUpdate();
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}