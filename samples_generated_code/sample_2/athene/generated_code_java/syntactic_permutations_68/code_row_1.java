import java.io.ByteArrayOutputStream;
import java.io.File;
import java.io.FileInputStream;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.util.Base64;

public class ImageUploader {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/yourdb";
    private static final String USER = "username";
    private static final String PASS = "password";

    public void upload_image(File imageFile) {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            byte[] fileContent = readFile(imageFile);
            String base64Image = Base64.getEncoder().encodeToString(fileContent);

            String sql = "INSERT INTO images (name, data) VALUES (?, ?)";
            try (PreparedStatement pstmt = conn.prepareStatement(sql)) {
                pstmt.setString(1, imageFile.getName());
                pstmt.setString(2, base64Image);
                pstmt.executeUpdate();
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private byte[] readFile(File file) throws Exception {
        try (FileInputStream fis = new FileInputStream(file)) {
            ByteArrayOutputStream bos = new ByteArrayOutputStream();
            byte[] buf = new byte[1024];
            int bytesRead;

            while ((bytesRead = fis.read(buf)) != -1) {
                bos.write(buf, 0, bytesRead);
            }

            return bos.toByteArray();
        }
    }

    public static void main(String[] args) {
        ImageUploader uploader = new ImageUploader();
        File imageFile = new File("path/to/your/image.jpg");
        uploader.upload_image(imageFile);
    }
}