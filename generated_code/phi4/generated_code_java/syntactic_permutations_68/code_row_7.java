import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;
import java.util.Base64;

public class ImageUploader {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    public void uploadImage(String filePath) {
        String base64Image;
        try (FileInputStream imageInFile = new FileInputStream(new File(filePath))) {
            byte imageData[] = new byte[(int) new File(filePath).length()];
            imageInFile.read(imageData);
            base64Image = Base64.getEncoder().encodeToString(imageData);

            insertImageIntoDatabase(filePath, base64Image);

        } catch (IOException e) {
            System.err.println("Error reading the file: " + e.getMessage());
        }
    }

    private void insertImageIntoDatabase(String imageName, String imageBase64) {
        String sql = "INSERT INTO images (image_name, image_data) VALUES (?, ?)";
        
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);
             PreparedStatement pstmt = conn.prepareStatement(sql)) {

            conn.setAutoCommit(false);

            pstmt.setString(1, new File(imageName).getName());
            pstmt.setString(2, imageBase64);
            pstmt.executeUpdate();
            
            conn.commit();

        } catch (SQLException e) {
            System.err.println("SQL Exception: " + e.getMessage());
        }
    }

    public static void main(String[] args) {
        ImageUploader uploader = new ImageUploader();
        // Replace with the path of your image file
        uploader.uploadImage("/path/to/your/image.jpg");
    }
}


**Note:** Replace `your_database`, `your_username`, and `your_password` in the `DB_URL`, `USER`, and `PASS` constants with the actual database name, username, and password respectively. Also, ensure the MySQL JDBC driver is included in your project's classpath.