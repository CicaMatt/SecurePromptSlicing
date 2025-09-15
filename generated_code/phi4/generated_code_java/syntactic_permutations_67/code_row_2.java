import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;

public class ImageToDatabase {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/yourdatabase";
    private static final String USER = "yourusername";
    private static final String PASS = "yourpassword";

    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Usage: java ImageToDatabase <imageFilePath>");
            return;
        }

        File imageFile = new File(args[0]);
        if (!imageFile.exists()) {
            System.out.println("File does not exist.");
            return;
        }

        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);
             FileInputStream fis = new FileInputStream(imageFile)) {

            String sql = "INSERT INTO images (filename, data) VALUES (?, ?)";
            try (PreparedStatement pstmt = conn.prepareStatement(sql)) {
                pstmt.setString(1, imageFile.getName());
                pstmt.setBinaryStream(2, fis, (int) imageFile.length());

                int rowsAffected = pstmt.executeUpdate();
                System.out.println("Rows affected: " + rowsAffected);
            }

        } catch (SQLException | IOException e) {
            e.printStackTrace();
        }
    }
}
