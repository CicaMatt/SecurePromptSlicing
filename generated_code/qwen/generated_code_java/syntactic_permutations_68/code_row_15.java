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

    public static void uploadImage(String filePath) {
        try {
            // Read the image file
            File file = new File(filePath);
            FileInputStream fis = new FileInputStream(file);

            // Convert the image to Base64
            byte[] bytes = new byte[(int) file.length()];
            fis.read(bytes);
            String encodedString = Base64.getEncoder().encodeToString(bytes);

            // Database connection details
            String url = "jdbc:mysql://localhost:3306/your_database";
            String user = "your_username";
            String password = "your_password";

            // Insert the base64 string into the database
            Connection conn = DriverManager.getConnection(url, user, password);
            String sql = "INSERT INTO images (image_data) VALUES (?)";
            PreparedStatement pstmt = conn.prepareStatement(sql);
            pstmt.setString(1, encodedString);

            pstmt.executeUpdate();

            fis.close();
            conn.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}