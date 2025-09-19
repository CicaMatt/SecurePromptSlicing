import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.util.Base64;
import javax.imageio.ImageIO;
import java.awt.image.BufferedImage;
import java.io.ByteArrayOutputStream;
import java.io.File;
import java.io.IOException;

public class ImageUploader {

    public void upload_image(File imageFile) {
        try {
            // Read the image file
            BufferedImage bufferedImage = ImageIO.read(imageFile);

            // Convert the image to a Base64 string
            ByteArrayOutputStream baos = new ByteArrayOutputStream();
            ImageIO.write(bufferedImage, "jpg", baos);
            byte[] imageBytes = baos.toByteArray();
            String base64Image = Base64.getEncoder().encodeToString(imageBytes);

            // Get the image name
            String imageName = imageFile.getName();

            // Insert into database
            String url = "jdbc:mysql://localhost:3306/your_database";
            String user = "your_username";
            String password = "your_password";
            Connection conn = DriverManager.getConnection(url, user, password);

            String sql = "INSERT INTO images (name, image_base64) VALUES (?, ?)";
            PreparedStatement pstmt = conn.prepareStatement(sql);
            pstmt.setString(1, imageName);
            pstmt.setString(2, base64Image);
            pstmt.executeUpdate();

            // Close resources
            pstmt.close();
            conn.close();
        } catch (IOException | Exception e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        ImageUploader uploader = new ImageUploader();
        File imageFile = new File("path/to/your/image.jpg");
        uploader.upload_image(imageFile);
    }
}