import java.io.File;
import java.io.FileInputStream;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;

public class ImageUploader {

    public static void main(String[] args) {
        String jdbcURL = "jdbc:mysql://localhost:3306/yourDatabaseName";
        String dbUser = "yourUsername";
        String dbPassword = "yourPassword";

        String filePath = "path/to/your/image.jpg"; // Path to the image file
        String sql = "INSERT INTO images (image) VALUES (?)";

        try (Connection connection = DriverManager.getConnection(jdbcURL, dbUser, dbPassword);
             FileInputStream inputStream = new FileInputStream(new File(filePath));
             PreparedStatement preparedStatement = connection.prepareStatement(sql)) {

            preparedStatement.setBinaryStream(1, inputStream);
            int row = preparedStatement.executeUpdate();
            if (row > 0) {
                System.out.println("The file has been uploaded successfully.");
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
