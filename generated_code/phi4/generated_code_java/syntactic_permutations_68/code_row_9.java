import java.io.*;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.util.Base64;

public class ImageUploader {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    public static void main(String[] args) {
        File imageFile = new File("path/to/image.jpg");
        uploadImage(imageFile);
    }

    public static void uploadImage(File imageFile) {
        try (BufferedInputStream bis = new BufferedInputStream(new FileInputStream(imageFile));
             ByteArrayOutputStream baos = new ByteArrayOutputStream()) {

            byte[] buffer = new byte[1024];
            int bytesRead;

            while ((bytesRead = bis.read(buffer)) != -1) {
                baos.write(buffer, 0, bytesRead);
            }

            String base64Image = Base64.getEncoder().encodeToString(baos.toByteArray());

            try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {

                String sql = "INSERT INTO images (image_name, image_data) VALUES (?, ?)";
                try (PreparedStatement pstmt = conn.prepareStatement(sql)) {
                    pstmt.setString(1, imageFile.getName());
                    pstmt.setString(2, base64Image);
                    pstmt.executeUpdate();
                }
            }

        } catch (IOException | SQLException e) {
            e.printStackTrace();
        }
    }
}
