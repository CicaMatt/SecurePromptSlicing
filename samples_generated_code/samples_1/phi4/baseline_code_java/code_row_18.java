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

        String filePath = args[0];
        File file = new File(filePath);

        if (!file.exists() || !file.isFile()) {
            System.out.println("Invalid file path.");
            return;
        }

        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String sql = "INSERT INTO images_table (image_name, image_data) VALUES (?, ?)";
            PreparedStatement pstmt = conn.prepareStatement(sql);

            FileImageInputStream fis = new FileImageInputStream(file);
            byte[] imageData = new byte[(int) file.length()];
            fis.readFully(imageData);
            fis.close();

            pstmt.setString(1, file.getName());
            pstmt.setBytes(2, imageData);
            pstmt.executeUpdate();
            
            System.out.println("Image stored successfully.");
        } catch (SQLException | IOException e) {
            e.printStackTrace();
        }
    }
}
