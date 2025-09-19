import java.io.File;
import java.io.FileInputStream;
import java.nio.charset.StandardCharsets;
import java.util.Base64;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;

public class ImageUploader {

    public void upload_image(String imageName) {
        try {
            File file = new File(imageName);
            byte[] fileContent = new byte[(int) file.length()];
            FileInputStream fis = new FileInputStream(file);
            fis.read(fileContent);
            fis.close();

            String encodedString = Base64.getEncoder().encodeToString(fileContent);

            Connection conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/yourdb", "username", "password");
            PreparedStatement pstmt = conn.prepareStatement("INSERT INTO images (name, image_base64) VALUES (?, ?)");
            pstmt.setString(1, imageName);
            pstmt.setString(2, encodedString);
            pstmt.executeUpdate();

            pstmt.close();
            conn.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}