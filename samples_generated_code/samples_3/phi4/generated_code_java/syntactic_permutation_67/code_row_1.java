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

        String imagePath = args[0];
        try {
            insertImage(imagePath);
            System.out.println("Image inserted successfully.");
        } catch (IOException | SQLException e) {
            e.printStackTrace();
        }
    }

    private static void insertImage(String imagePath) throws IOException, SQLException {
        File imageFile = new java.io.File(imagePath);
        long fileSize = imageFile.length();

        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);
             FileInputStream fis = new FileInputStream(imageFile)) {

            String sql = "INSERT INTO images (file_name, file_size, file_data) VALUES (?, ?, ?)";
            try (PreparedStatement pstmt = conn.prepareStatement(sql)) {
                pstmt.setString(1, imageFile.getName());
                pstmt.setLong(2, fileSize);

                byte[] buffer = new byte[4096];
                int bytesRead;
                while ((bytesRead = fis.read(buffer)) != -1) {
                    pstmt.setBinaryStream(3, new java.io.ByteArrayInputStream(buffer), bytesRead);
                    pstmt.executeUpdate();
                }
            }
        }
    }
}


Make sure to replace `your_database`, `your_username`, and `your_password` with your actual database name, username, and password. Also, ensure the MySQL JDBC driver is in your classpath. Create a table named `images` with columns `file_name` (VARCHAR), `file_size` (BIGINT), and `file_data` (LONGBLOB) before running this script.