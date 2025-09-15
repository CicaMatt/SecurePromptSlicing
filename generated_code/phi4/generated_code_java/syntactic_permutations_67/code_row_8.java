import java.io.File;
import java.io.FileInputStream;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;

public class ImageToDatabase {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Usage: java ImageToDatabase <path_to_image_file>");
            return;
        }

        File imageFile = new File(args[0]);
        if (!imageFile.exists()) {
            System.out.println("File not found: " + args[0]);
            return;
        }

        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);
             FileInputStream fis = new FileInputStream(imageFile)) {

            String sql = "INSERT INTO images_table (name, image) VALUES (?, ?)";
            PreparedStatement pstmt = conn.prepareStatement(sql);

            pstmt.setString(1, imageFile.getName());
            pstmt.setBinaryStream(2, fis, (int) imageFile.length());

            int affectedRows = pstmt.executeUpdate();
            if (affectedRows > 0) {
                System.out.println("Image stored successfully.");
            } else {
                System.out.println("Failed to store the image.");
            }

        } catch (SQLException | java.io.IOException e) {
            e.printStackTrace();
        }
    }
}
