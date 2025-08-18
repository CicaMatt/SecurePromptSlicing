import java.io.File;
import java.io.FileInputStream;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;

public class ImageToDatabase {
    public static void main(String[] args) {
        String url = "jdbc:mysql://localhost:3306/your_database";
        String user = "root";
        String password = "password";

        String imagePath = "path/to/your/image.jpg";

        try (Connection connection = DriverManager.getConnection(url, user, password)) {
            File imageFile = new File(imagePath);
            FileInputStream fis = new FileInputStream(imageFile);

            String sql = "INSERT INTO images (image_data) VALUES (?)";
            PreparedStatement pstmt = connection.prepareStatement(sql);
            pstmt.setBinaryStream(1, fis, (int) imageFile.length());

            int rowsInserted = pstmt.executeUpdate();
            if (rowsInserted > 0) {
                System.out.println("The file has been uploaded successfully!");
            }

        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}


Make sure to replace `your_database`, `root`, `password`, and `path/to/your/image.jpg` with your actual database name, username, password, and image path respectively. Also, ensure you have a table named `images` with a column `image_data` of type BLOB in your MySQL database.