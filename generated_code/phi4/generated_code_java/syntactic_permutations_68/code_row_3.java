import java.awt.image.BufferedImage;
import java.io.ByteArrayOutputStream;
import java.io.File;
import java.io.FileInputStream;
import javax.imageio.ImageIO;
import java.util.Base64;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;

public class ImageUploader {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    public void uploadImage(File imageFile) throws Exception {
        // Convert image to Base64
        BufferedImage bufferedImage = ImageIO.read(new FileInputStream(imageFile));
        ByteArrayOutputStream baos = new ByteArrayOutputStream();
        ImageIO.write(bufferedImage, "png", baos);
        byte[] imageDataBytes = baos.toByteArray();
        String base64String = Base64.getEncoder().encodeToString(imageDataBytes);

        // Insert into database
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String sql = "INSERT INTO images (image_name, image_data) VALUES (?, ?)";
            try (PreparedStatement pstmt = conn.prepareStatement(sql)) {
                pstmt.setString(1, imageFile.getName());
                pstmt.setString(2, base64String);
                pstmt.executeUpdate();
            }
        }
    }

    public static void main(String[] args) throws Exception {
        ImageUploader uploader = new ImageUploader();
        File imageFile = new File("path/to/your/image.png");
        uploader.uploadImage(imageFile);
    }
}


Make sure to replace `your_database`, `your_username`, and `your_password` with your actual database credentials, and update the file path in `main` method with the location of the image you want to upload. Also, ensure that MySQL JDBC driver is added to your project's dependencies.