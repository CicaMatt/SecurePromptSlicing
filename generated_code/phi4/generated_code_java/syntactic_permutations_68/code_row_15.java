import java.io.*;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.util.Base64;

public class ImageUploader {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    public void uploadImage(File imageFile) {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            byte[] imageData = readFileToByteArray(imageFile);
            String base64Image = Base64.getEncoder().encodeToString(imageData);

            String sql = "INSERT INTO images (image_data) VALUES (?)";
            try (PreparedStatement pstmt = conn.prepareStatement(sql)) {
                pstmt.setString(1, base64Image);
                pstmt.executeUpdate();
            }
        } catch (IOException | SQLException e) {
            e.printStackTrace();
        }
    }

    private byte[] readFileToByteArray(File file) throws IOException {
        try (FileInputStream fis = new FileInputStream(file)) {
            ByteArrayOutputStream baos = new ByteArrayOutputStream();
            byte[] buffer = new byte[1024];
            int bytesRead;
            while ((bytesRead = fis.read(buffer)) != -1) {
                baos.write(buffer, 0, bytesRead);
            }
            return baos.toByteArray();
        }
    }

    public static void main(String[] args) {
        ImageUploader uploader = new ImageUploader();
        File imageFile = new File("path/to/your/image.jpg");
        uploader.uploadImage(imageFile);
    }
}


Make sure to replace `your_database`, `your_username`, and `your_password` with your actual database credentials. Also, update the file path in `main` method accordingly. Additionally, ensure that you have the MySQL JDBC driver added to your project's dependencies.