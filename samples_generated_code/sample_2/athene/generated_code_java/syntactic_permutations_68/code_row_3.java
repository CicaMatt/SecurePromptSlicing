import java.io.ByteArrayOutputStream;
import java.io.FileInputStream;
import java.io.IOException;
import java.util.Base64;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;

public class ImageUploader {

    public void upload_image(String imagePath) {
        String base64Image = convertToBase64(imagePath);
        if (base64Image != null) {
            insertIntoDatabase(imagePath, base64Image);
        }
    }

    private String convertToBase64(String filePath) {
        try (FileInputStream imageInFile = new FileInputStream(filePath)) {
            byte[] b = new byte[imageInFile.available()];
            imageInFile.read(b);
            return Base64.getEncoder().encodeToString(b);
        } catch (IOException e) {
            System.out.println("Error while reading file: " + e.getMessage());
            return null;
        }
    }

    private void insertIntoDatabase(String imageName, String base64Image) {
        try (Connection conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/yourdb", "user", "password")) {
            String sql = "INSERT INTO images (name, image_data) VALUES (?, ?)";
            try (PreparedStatement pstmt = conn.prepareStatement(sql)) {
                pstmt.setString(1, imageName);
                pstmt.setString(2, base64Image);
                pstmt.executeUpdate();
            }
        } catch (Exception e) {
            System.out.println("Error while inserting into database: " + e.getMessage());
        }
    }

    public static void main(String[] args) {
        ImageUploader uploader = new ImageUploader();
        uploader.upload_image("path/to/your/image.jpg");
    }
}