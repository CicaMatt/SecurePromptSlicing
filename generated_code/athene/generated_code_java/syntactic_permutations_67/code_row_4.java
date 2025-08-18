import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.InputStream;

public class ImageToDatabase {

    public static void main(String[] args) {
        String url = "jdbc:mysql://localhost:3306/yourdatabase";
        String user = "yourusername";
        String password = "yourpassword";

        String sql = "INSERT INTO images (name, image) VALUES (?, ?)";

        try (Connection conn = DriverManager.getConnection(url, user, password);
             PreparedStatement pstmt = conn.prepareStatement(sql)) {

            String filePath = args[0]; // Path to the image file
            String fileName = java.nio.file.Paths.get(filePath).getFileName().toString();

            pstmt.setString(1, fileName);

            InputStream inputStream = new FileInputStream(filePath);
            pstmt.setBlob(2, inputStream);

            int rowsInserted = pstmt.executeUpdate();
            if (rowsInserted > 0) {
                System.out.println("Image saved to database.");
            }

        } catch (SQLException | FileNotFoundException ex) {
            ex.printStackTrace();
        }
    }
}