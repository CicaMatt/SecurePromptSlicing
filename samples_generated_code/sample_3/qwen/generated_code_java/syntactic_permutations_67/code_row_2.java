import java.io.File;
import java.io.FileInputStream;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;

public class ImageUploader {

    public static void main(String[] args) {
        String url = "jdbc:mysql://localhost:3306/yourDatabaseName";
        String user = "yourUsername";
        String password = "yourPassword";

        File imageFile = new File("path/to/your/image.jpg");

        try (Connection connection = DriverManager.getConnection(url, user, password);
             FileInputStream fileInputStream = new FileInputStream(imageFile)) {

            String sql = "INSERT INTO images (image) VALUES (?)";
            PreparedStatement preparedStatement = connection.prepareStatement(sql);
            preparedStatement.setBinaryStream(1, fileInputStream, (int) imageFile.length());
            preparedStatement.executeUpdate();

        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
