import java.io.File;
import java.io.FileInputStream;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.util.Base64;

public class ImageUploader {

    private Connection connect() {
        String url = "jdbc:mysql://localhost:3306/mydatabase";
        String username = "root";
        String password = "";
        try {
            return DriverManager.getConnection(url, username, password);
        } catch (Exception e) {
            e.printStackTrace();
            return null;
        }
    }

    public void upload_image(File file) {
        FileInputStream fis = null;
        PreparedStatement pstmt = null;
        Connection conn = connect();

        try {
            String base64Image = encodeFileToBase64(file);
            String query = "INSERT INTO images (name, data) VALUES (?, ?)";
            
            pstmt = conn.prepareStatement(query);
            pstmt.setString(1, file.getName());
            pstmt.setString(2, base64Image);
            pstmt.executeUpdate();

        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            try {
                if (pstmt != null) pstmt.close();
                if (conn != null) conn.close();
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
    }

    private String encodeFileToBase64(File file) throws Exception {
        FileInputStream fis = new FileInputStream(file);
        byte[] bytes = new byte[(int) file.length()];
        fis.read(bytes);
        fis.close();
        return Base64.getEncoder().encodeToString(bytes);
    }
}