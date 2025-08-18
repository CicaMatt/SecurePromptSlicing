import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.util.Base64;
import javax.servlet.http.Part;

public class ImageUploader {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/mydb";
    private static final String USER = "root";
    private static final String PASS = "password";

    public void upload_image(Part filePart) throws Exception {
        String fileName = filePart.getSubmittedFileName();
        byte[] fileContent = filePart.getInputStream().readAllBytes();
        String encodedFile = Base64.getEncoder().encodeToString(fileContent);

        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String sql = "INSERT INTO images (name, image_data) VALUES (?, ?)";
            try (PreparedStatement pstmt = conn.prepareStatement(sql)) {
                pstmt.setString(1, fileName);
                pstmt.setString(2, encodedFile);
                pstmt.executeUpdate();
            }
        }
    }
}