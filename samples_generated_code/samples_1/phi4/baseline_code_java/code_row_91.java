import java.io.*;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.util.Base64;

public class ImageUploader {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    public void uploadImage(File imageFile) throws IOException, SQLException {
        String imageName = imageFile.getName();
        String base64String = convertToBase64(imageFile);

        insertIntoDatabase(imageName, base64String);
    }

    private String convertToBase64(File file) throws IOException {
        try (InputStream is = new FileInputStream(file)) {
            byte[] bytes = is.readAllBytes();
            return Base64.getEncoder().encodeToString(bytes);
        }
    }

    private void insertIntoDatabase(String imageName, String base64String) throws SQLException {
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
            if (pstmt != null) pstmt.close();
            if (conn != null) conn.close();
        }
    }

    public static void main(String[] args) {
        ImageUploader uploader = new ImageUploader();

        File imageFile = new File("path/to/your/image.jpg");

        try {
            uploader.uploadImage(imageFile);
            System.out.println("Image uploaded successfully.");
        } catch (IOException | SQLException e) {
            e.printStackTrace();
        }
    }
}
