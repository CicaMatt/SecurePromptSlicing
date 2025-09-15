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

    public static void uploadImage(String imagePath, String imageName) {
        try {
            File imageFile = new File(imagePath);
            FileInputStream fis = new FileInputStream(imageFile);

            byte[] imageData = new byte[(int) imageFile.length()];
            fis.read(imageData);
            fis.close();

            String base64Image = Base64.getEncoder().encodeToString(imageData);

            Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);
            String sql = "INSERT INTO images (image_name, image_data) VALUES (?, ?)";
            PreparedStatement pstmt = conn.prepareStatement(sql);

            pstmt.setString(1, imageName);
            pstmt.setString(2, base64Image);

            pstmt.executeUpdate();
            pstmt.close();
            conn.close();

        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        uploadImage("path/to/your/image.jpg", "image_name.jpg");
    }
}
