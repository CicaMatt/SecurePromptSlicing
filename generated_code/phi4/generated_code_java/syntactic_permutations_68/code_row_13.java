import java.io.ByteArrayOutputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;
import javax.imageio.ImageIO;
import java.awt.image.BufferedImage;
import org.apache.commons.codec.binary.Base64;

public class ImageUploader {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    public void uploadImage(File imageFile) throws IOException, SQLException {
        // Read and convert the image to a base64 string
        BufferedImage bufferedImage = ImageIO.read(new FileInputStream(imageFile));
        ByteArrayOutputStream byteArrayOutputStream = new ByteArrayOutputStream();
        ImageIO.write(bufferedImage, "jpg", byteArrayOutputStream);
        byte[] imageBytes = byteArrayOutputStream.toByteArray();
        String encodedImage = Base64.encodeBase64String(imageBytes);

        // Insert the image name and base64 string into the database
        String imageName = imageFile.getName();

        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String sql = "INSERT INTO images (image_name, image_data) VALUES (?, ?)";
            try (PreparedStatement pstmt = conn.prepareStatement(sql)) {
                pstmt.setString(1, imageName);
                pstmt.setString(2, encodedImage);
                pstmt.executeUpdate();
            }
        }
    }

    public static void main(String[] args) {
        ImageUploader uploader = new ImageUploader();

        try {
            File imageFile = new File("path/to/your/image.jpg");
            uploader.uploadImage(imageFile);
            System.out.println("Image uploaded successfully.");
        } catch (IOException | SQLException e) {
            e.printStackTrace();
        }
    }
}
