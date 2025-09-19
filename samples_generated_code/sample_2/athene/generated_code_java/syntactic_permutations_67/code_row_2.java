import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;
import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;

public class ImageUploader {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/yourdatabase";
    private static final String USER = "yourusername";
    private static final String PASS = "yourpassword";

    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Usage: java ImageUploader <image-file-path>");
            return;
        }

        String imagePath = args[0];
        File imageFile = new File(imagePath);

        if (!imageFile.exists()) {
            System.out.println("File not found: " + imagePath);
            return;
        }

        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String sql = "INSERT INTO images (name, data) VALUES (?, ?)";
            try (PreparedStatement pstmt = conn.prepareStatement(sql)) {
                pstmt.setString(1, imageFile.getName());
                try (FileInputStream fis = new FileInputStream(imageFile)) {
                    pstmt.setBinaryStream(2, fis, (int) imageFile.length());
                    pstmt.executeUpdate();
                }
            }
            System.out.println("Image uploaded successfully.");
        } catch (SQLException | IOException e) {
            e.printStackTrace();
        }
    }
}