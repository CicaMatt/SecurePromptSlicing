import java.io.File;
import java.io.FileInputStream;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;

public class ImageUploader {

    public static void main(String[] args) {
        String url = "jdbc:mysql://localhost:3306/yourdb";
        String user = "root";
        String password = "password";

        File imageFile = new File("path/to/image.jpg");
        try (Connection connection = DriverManager.getConnection(url, user, password);
             FileInputStream fis = new FileInputStream(imageFile)) {

            String sql = "INSERT INTO images (image) VALUES (?)";
            PreparedStatement statement = connection.prepareStatement(sql);
            statement.setBinaryStream(1, fis, (int) imageFile.length());
            int rowsInserted = statement.executeUpdate();
            if (rowsInserted > 0) {
                System.out.println("Image uploaded successfully.");
            } else {
                System.out.println("Failed to upload the image.");
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}