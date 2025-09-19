import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;

public class ImageToDatabase {
    private static final String URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASSWORD = "your_password";

    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Usage: java ImageToDatabase <image_file_path>");
            return;
        }

        File imageFile = new File(args[0]);
        try (FileInputStream fis = new FileInputStream(imageFile)) {
            byte[] imageData = new byte[(int) imageFile.length()];
            fis.read(imageData);

            storeImageInDatabase(imageData);
        } catch (IOException e) {
            System.out.println("Error reading the image file: " + e.getMessage());
        }
    }

    private static void storeImageInDatabase(byte[] imageData) {
        String sql = "INSERT INTO images (image_data, content_type) VALUES (?, ?)";

        try (Connection conn = DriverManager.getConnection(URL, USER, PASSWORD);
             PreparedStatement pstmt = conn.prepareStatement(sql)) {

            pstmt.setBytes(1, imageData);
            pstmt.setString(2, getFileContentType(imageData));

            int affectedRows = pstmt.executeUpdate();
            if (affectedRows > 0) {
                System.out.println("Image stored successfully.");
            } else {
                System.out.println("Failed to store the image.");
            }
        } catch (SQLException e) {
            System.out.println("Database error: " + e.getMessage());
        }
    }

    private static String getFileContentType(byte[] imageData) {
        // A simple check for JPEG and PNG. Extend as needed.
        if (imageData[0] == (byte) 0xFF && imageData[1] == (byte) 0xD8) {
            return "image/jpeg";
        } else if (imageData[0] == (byte) 0x89 && imageData[1] == (byte) 0x50) {
            return "image/png";
        }
        return "application/octet-stream";
    }
}


**Note:** Before running this code, ensure you have:
- A MySQL database set up with a table named `images` having at least two columns: `image_data` (BLOB type) and `content_type` (VARCHAR).
- The MySQL JDBC driver included in your classpath. You can download it from the official website or add it via Maven/Gradle dependencies.
- Replace `your_database`, `your_username`, and `your_password` with your actual database name, username, and password.