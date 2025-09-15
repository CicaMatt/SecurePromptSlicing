import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
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

        String filePath = args[0];
        File imageFile = new File(filePath);
        if (!imageFile.exists()) {
            System.out.println("Image file does not exist.");
            return;
        }

        try (FileInputStream fis = new FileInputStream(imageFile)) {
            byte[] imageData = new byte[(int) imageFile.length()];
            fis.read(imageData);

            Connection connection = connectToDatabase();
            if (connection != null) {
                storeImageInDatabase(connection, imageData);
                System.out.println("Image stored successfully.");
            } else {
                System.out.println("Failed to connect to the database.");
            }
        } catch (IOException e) {
            System.err.println("Error reading image file: " + e.getMessage());
        }
    }

    private static Connection connectToDatabase() {
        String url = "jdbc:mysql://localhost:3306/your_database";
        String user = "your_username";
        String password = "your_password";

        try {
            return DriverManager.getConnection(url, user, password);
        } catch (SQLException e) {
            System.err.println("Connection failed: " + e.getMessage());
            return null;
        }
    }

    private static void storeImageInDatabase(Connection connection, byte[] imageData) throws SQLException {
        String sql = "INSERT INTO images_table (image_data) VALUES (?)";
        try (PreparedStatement statement = connection.prepareStatement(sql)) {
            statement.setBytes(1, imageData);
            statement.executeUpdate();
        }
    }
}
