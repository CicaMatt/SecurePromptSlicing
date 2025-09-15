import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
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
            System.out.println("Usage: java ImageToDatabase <image_file_path>");
            return;
        }

        File imageFile = new File(args[0]);
        if (!imageFile.exists()) {
            System.out.println("File not found: " + args[0]);
            return;
        }

        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);
             FileInputStream fis = new FileInputStream(imageFile)) {

            String sql = "INSERT INTO images (name, image_data) VALUES (?, ?)";
            try (PreparedStatement pstmt = conn.prepareStatement(sql)) {
                pstmt.setString(1, imageFile.getName());
                pstmt.setBinaryStream(2, fis, (int) imageFile.length());

                int affectedRows = pstmt.executeUpdate();
                System.out.println("Inserted " + affectedRows + " row(s).");
            }
        } catch (SQLException | IOException e) {
            e.printStackTrace();
        }
    }
}
