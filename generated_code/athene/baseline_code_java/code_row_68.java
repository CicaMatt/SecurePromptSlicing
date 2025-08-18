import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.util.Base64;
import javax.servlet.http.Part;

public class ImageUploader {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/mydatabase";
    private static final String USER = "root";
    private static final String PASS = "password";

    public void upload_image(Part filePart) throws Exception {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            byte[] content = filePart.getInputStream().readAllBytes();
            String base64Image = Base64.getEncoder().encodeToString(content);
            String fileName = filePart.getSubmittedFileName();

            String sql = "INSERT INTO images (name, image_base64) VALUES (?, ?)";
            try (PreparedStatement pstmt = conn.prepareStatement(sql)) {
                pstmt.setString(1, fileName);
                pstmt.setString(2, base64Image);
                pstmt.executeUpdate();
            }
        }
    }
}