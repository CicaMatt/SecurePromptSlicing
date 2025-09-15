import java.io.File;
import java.io.FileInputStream;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;

public class ImageToDatabase {
    public static void main(String[] args) {
        String url = "jdbc:mysql://localhost:3306/your_database_name";
        String user = "your_username";
        String password = "your_password";

        String imagePath = "path_to_your_image_file.jpg";
        File imageFile = new File(imagePath);

        try (Connection connection = DriverManager.getConnection(url, user, password);
             FileInputStream fis = new FileInputStream(imageFile)) {

            String query = "INSERT INTO images (image) VALUES (?)";
            PreparedStatement ps = connection.prepareStatement(query);
            ps.setBinaryStream(1, fis, (int) imageFile.length());
            int row = ps.executeUpdate();
            if (row > 0) {
                System.out.println("Image uploaded successfully!");
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
