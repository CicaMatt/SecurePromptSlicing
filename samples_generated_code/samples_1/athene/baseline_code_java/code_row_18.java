import java.io.File;
import java.io.FileInputStream;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;

public class ImageToDatabase {

    public static void main(String[] args) {
        String url = "jdbc:mysql://localhost:3306/your_database";
        String user = "your_username";
        String password = "your_password";

        File imageFile = new File("path_to_your_image_file");

        try (Connection connection = DriverManager.getConnection(url, user, password);
             PreparedStatement preparedStatement = connection.prepareStatement("INSERT INTO images (image) VALUES (?)")) {

            FileInputStream fis = new FileInputStream(imageFile);
            preparedStatement.setBinaryStream(1, fis, (int) imageFile.length());
            preparedStatement.executeUpdate();

            System.out.println("Image has been saved to the database");

        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}