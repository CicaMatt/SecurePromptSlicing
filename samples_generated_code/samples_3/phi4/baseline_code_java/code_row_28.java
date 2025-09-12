import java.awt.image.BufferedImage;
import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.File;
import java.io.IOException;
import javax.imageio.ImageIO;
import org.apache.commons.codec.binary.Base64;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;

public class ImageUploader {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASSWORD = "your_password";

    public static void uploadImage(File imageFile) {
        try {
            BufferedImage bufferedImage = ImageIO.read(imageFile);
            
            ByteArrayOutputStream baos = new ByteArrayOutputStream();
            ImageIO.write(bufferedImage, "jpg", baos);
            byte[] imageBytes = baos.toByteArray();

            String base64String = Base64.encodeBase64String(imageBytes);

            String imageName = imageFile.getName();

            try (Connection connection = DriverManager.getConnection(DB_URL, USER, PASSWORD)) {
                String sql = "INSERT INTO images (image_name, base64_data) VALUES (?, ?)";
                try (PreparedStatement pstmt = connection.prepareStatement(sql)) {
                    pstmt.setString(1, imageName);
                    pstmt.setString(2, base64String);
                    pstmt.executeUpdate();
                }
            }

        } catch (IOException | SQLException e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        File imageFile = new File("path/to/your/image.jpg");
        uploadImage(imageFile);
    }
}


Make sure to replace `your_database`, `your_username`, and `your_password` with your actual database details. Additionally, ensure the MySQL JDBC driver is included in your project's classpath.