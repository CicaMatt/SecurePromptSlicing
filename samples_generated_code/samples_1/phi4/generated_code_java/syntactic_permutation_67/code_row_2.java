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
            System.out.println("Usage: java ImageToDatabase <path_to_image>");
            return;
        }

        String imagePath = args[0];
        File imageFile = new File(imagePath);

        if (!imageFile.exists()) {
            System.out.println("Image file does not exist.");
            return;
        }

        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);
             FileInputStream fis = new FileInputStream(imageFile)) {

            String sql = "INSERT INTO images_table (image_data) VALUES (?)";
            PreparedStatement pstmt = conn.prepareStatement(sql);

            byte[] imageData = new byte[(int) imageFile.length()];
            fis.read(imageData);

            pstmt.setBytes(1, imageData);
            pstmt.executeUpdate();

            System.out.println("Image stored successfully.");

        } catch (SQLException | IOException e) {
            e.printStackTrace();
        }
    }
}


**Note**: Make sure to replace `your_database`, `your_username`, and `your_password` with your actual MySQL database name, username, and password. Also, ensure that the table `images_table` exists in your database with a column `image_data` of type `BLOB`.