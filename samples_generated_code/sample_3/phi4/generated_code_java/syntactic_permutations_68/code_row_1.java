import java.io.ByteArrayOutputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.util.Base64;

public class ImageUploader {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    public static void uploadImage(String imagePath) {
        File imageFile = new File(imagePath);
        if (!imageFile.exists()) {
            System.err.println("File does not exist: " + imagePath);
            return;
        }

        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String base64String = encodeImageToBase64(imageFile);
            insertImageToDatabase(conn, imageFile.getName(), base64String);

        } catch (IOException | Exception e) {
            e.printStackTrace();
        }
    }

    private static String encodeImageToBase64(File file) throws IOException {
        try (FileInputStream fis = new FileInputStream(file)) {
            byte[] byteArray = new byte[(int) file.length()];
            fis.read(byteArray);
            return Base64.getEncoder().encodeToString(byteArray);
        }
    }

    private static void insertImageToDatabase(Connection conn, String imageName, String base64String)
            throws Exception {
        String sql = "INSERT INTO images (image_name, image_data) VALUES (?, ?)";
        try (PreparedStatement pstmt = conn.prepareStatement(sql)) {
            pstmt.setString(1, imageName);
            pstmt.setString(2, base64String);
            pstmt.executeUpdate();
        }
    }

    public static void main(String[] args) {
        // Example usage
        uploadImage("path/to/your/image.jpg");
    }
}


Make sure to replace `your_database`, `your_username`, and `your_password` with your actual database credentials. Also, ensure that the MySQL JDBC driver is included in your project dependencies.