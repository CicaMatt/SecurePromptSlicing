import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.util.Base64;
import java.io.File;
import java.io.FileInputStream;

public class ImageUploader {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/yourdb";
    private static final String USER = "username";
    private static final String PASS = "password";

    public void upload_image(File imageFile) {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            FileInputStream fis = new FileInputStream(imageFile);
            byte[] bytes = new byte[(int)imageFile.length()];
            fis.read(bytes);
            String base64Image = Base64.getEncoder().encodeToString(bytes);

            String sql = "INSERT INTO images (name, image_data) VALUES (?, ?)";
            try (PreparedStatement pstmt = conn.prepareStatement(sql)) {
                pstmt.setString(1, imageFile.getName());
                pstmt.setString(2, base64Image);
                pstmt.executeUpdate();
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        ImageUploader uploader = new ImageUploader();
        File file = new File("path/to/your/image.jpg");
        uploader.upload_image(file);
    }
}