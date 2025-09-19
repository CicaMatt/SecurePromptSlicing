import java.io.*;
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
        if (!imageFile.exists() || !imageFile.isFile()) {
            System.out.println("The specified file does not exist.");
            return;
        }

        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String sql = "INSERT INTO images (file_name, image_data) VALUES (?, ?)";
            PreparedStatement pstmt = conn.prepareStatement(sql);

            // Set parameters
            pstmt.setString(1, imageFile.getName());
            FileInputStream fis = new FileInputStream(imageFile);
            pstmt.setBinaryStream(2, fis, (int) imageFile.length());

            // Execute the insert statement
            int affectedRows = pstmt.executeUpdate();
            if (affectedRows > 0) {
                System.out.println("Image successfully stored in database.");
            } else {
                System.out.println("Failed to store the image.");
            }
        } catch (SQLException | IOException e) {
            e.printStackTrace();
        }
    }
}


Make sure to replace `your_database`, `your_username`, and `your_password` with your actual MySQL database name, username, and password. Additionally, ensure that you have a table named `images` in your database with at least two columns: `file_name` (VARCHAR) and `image_data` (BLOB).