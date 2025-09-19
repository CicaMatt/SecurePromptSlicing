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
        String imagePath = "path_to_your_image_file";

        try (FileInputStream fis = new FileInputStream(new File(imagePath));
             Connection connection = DriverManager.getConnection(url, user, password)) {

            String query = "INSERT INTO images (image) VALUES (?)";
            PreparedStatement preparedStatement = connection.prepareStatement(query);
            preparedStatement.setBinaryStream(1, fis, fis.available());

            int rowsInserted = preparedStatement.executeUpdate();
            if (rowsInserted > 0) {
                System.out.println("A new row was inserted successfully!");
            }

        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
