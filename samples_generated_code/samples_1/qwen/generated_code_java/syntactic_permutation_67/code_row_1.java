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

        File imageFile = new File("path_to_your_image.jpg");

        try (Connection connection = DriverManager.getConnection(url, user, password);
             FileInputStream fis = new FileInputStream(imageFile);
             PreparedStatement preparedStatement = connection.prepareStatement("INSERT INTO images (image_data) VALUES (?)")) {

            preparedStatement.setBinaryStream(1, fis, (int) imageFile.length());
            preparedStatement.executeUpdate();

            System.out.println("Image stored successfully in the database.");

        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}



CREATE TABLE images (
    id INT AUTO_INCREMENT PRIMARY KEY,
    image_data LONGBLOB NOT NULL
);

Note: The SQL part is not Java code but is provided for reference to create the necessary table structure in MySQL. Ensure you have a MySQL server running and replace `your_database`, `your_username`, `your_password`, and `path_to_your_image.jpg` with actual values.