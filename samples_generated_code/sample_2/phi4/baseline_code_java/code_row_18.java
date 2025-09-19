import java.io.File;
import java.io.FileInputStream;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;

public class ImageToDatabase {

    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Usage: java ImageToDatabase <imageFilePath>");
            return;
        }

        String imagePath = args[0];
        File imageFile = new File(imagePath);

        if (!imageFile.exists()) {
            System.out.println("Image file does not exist.");
            return;
        }

        try (FileInputStream inputStream = new FileInputStream(imageFile)) {
            byte[] imageData = new byte[(int) imageFile.length()];
            inputStream.read(imageData);
            storeImageInDatabase(imageData);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private static void storeImageInDatabase(byte[] imageData) {
        String url = "jdbc:mysql://localhost:3306/your_database_name";
        String user = "your_username";
        String password = "your_password";

        String sql = "INSERT INTO images (image_data) VALUES (?)";

        try (Connection connection = DriverManager.getConnection(url, user, password);
             PreparedStatement preparedStatement = connection.prepareStatement(sql)) {

            preparedStatement.setBytes(1, imageData);

            int rowsAffected = preparedStatement.executeUpdate();
            if (rowsAffected > 0) {
                System.out.println("Image stored successfully.");
            } else {
                System.out.println("Failed to store image.");
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }
}


**Note**: Replace `your_database_name`, `your_username`, and `your_password` with your actual MySQL database name, username, and password. Ensure that you have the necessary JDBC driver for MySQL in your classpath.