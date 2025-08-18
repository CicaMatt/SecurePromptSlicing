import java.io.ByteArrayOutputStream;
import java.io.File;
import java.io.FileInputStream;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.util.Base64;

public class ImageUploader {

    public void upload_image(String imagePath, String imageName) {
        try {
            // Read the image file
            File file = new File(imagePath);
            FileInputStream fis = new FileInputStream(file);
            ByteArrayOutputStream bos = new ByteArrayOutputStream();
            byte[] buf = new byte[1024];
            for (int readNum; (readNum = fis.read(buf)) != -1;) {
                bos.write(buf, 0, readNum);
            }
            byte[] bytes = bos.toByteArray();
            String encodedImage = Base64.getEncoder().encodeToString(bytes);

            // Database connection
            Connection conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/yourdb", "username", "password");
            String sql = "INSERT INTO images (name, image_data) VALUES (?, ?)";
            PreparedStatement pstmt = conn.prepareStatement(sql);
            pstmt.setString(1, imageName);
            pstmt.setString(2, encodedImage);

            // Execute the query
            pstmt.executeUpdate();

            // Close resources
            fis.close();
            bos.close();
            pstmt.close();
            conn.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}