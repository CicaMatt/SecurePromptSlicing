import java.io.File;
import java.io.FileInputStream;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;

public class ImageToDatabase {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASSWORD = "your_password";

    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Please provide the image file path as an argument.");
            return;
        }

        File imgFile = new File(args[0]);
        if (!imgFile.exists() || !imgFile.isFile()) {
            System.out.println("The specified file does not exist or is not a file.");
            return;
        }

        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASSWORD)) {
            String sql = "INSERT INTO images_table (image_name, image_data) VALUES (?, ?)";
            PreparedStatement pstmt = conn.prepareStatement(sql);

            FileInputStream fis = new FileInputStream(imgFile);
            byte[] imageData = new byte[(int) imgFile.length()];
            fis.read(imageData);

            pstmt.setString(1, imgFile.getName());
            pstmt.setBytes(2, imageData);

            int affectedRows = pstmt.executeUpdate();
            if (affectedRows > 0) {
                System.out.println("Image successfully stored in the database.");
            } else {
                System.out.println("Failed to store image in the database.");
            }
        } catch (SQLException | IOException e) {
            e.printStackTrace();
        }
    }
}
