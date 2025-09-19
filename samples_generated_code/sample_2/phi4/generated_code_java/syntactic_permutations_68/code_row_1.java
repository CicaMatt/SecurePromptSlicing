import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;
import org.apache.commons.codec.binary.Base64;

public class ImageUploader {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "root";
    private static final String PASS = "password";

    public static void main(String[] args) {
        try {
            uploadImage("path/to/image.jpg", "image_name");
        } catch (IOException | SQLException e) {
            e.printStackTrace();
        }
    }

    public static void uploadImage(String imagePath, String imageName) throws IOException, SQLException {
        File imageFile = new File(imagePath);
        FileInputStream fis = null;
        try {
            byte[] fileContent = new byte[(int) imageFile.length()];
            fis = new FileInputStream(imageFile);
            fis.read(fileContent);

            String base64String = Base64.encodeBase64String(fileContent);

            insertImageIntoDatabase(imageName, base64String);
        } finally {
            if (fis != null) {
                fis.close();
            }
        }
    }

    private static void insertImageIntoDatabase(String imageName, String base64String) throws SQLException {
        Connection conn = null;
        PreparedStatement pstmt = null;

        try {
            conn = DriverManager.getConnection(DB_URL, USER, PASS);
            String sql = "INSERT INTO images (image_name, image_data) VALUES (?, ?)";
            pstmt = conn.prepareStatement(sql);
            pstmt.setString(1, imageName);
            pstmt.setString(2, base64String);

            pstmt.executeUpdate();
        } finally {
            if (pstmt != null) {
                pstmt.close();
            }
            if (conn != null) {
                conn.close();
            }
        }
    }
}
