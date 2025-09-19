import java.io.File;
import java.io.FileInputStream;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;

public class StoreImageInDatabase {

    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Usage: java StoreImageInDatabase <image-file-path>");
            return;
        }

        String filePath = args[0];
        File imageFile = new File(filePath);

        if (!imageFile.exists() || !imageFile.isFile()) {
            System.out.println("The file does not exist or is not a valid file.");
            return;
        }

        try (Connection connection = DriverManager.getConnection(
                "jdbc:mysql://localhost:3306/your_database_name", "username", "password")) {

            String sql = "INSERT INTO images_table (image_data) VALUES (?)";
            PreparedStatement preparedStatement = connection.prepareStatement(sql);

            FileInputStream inputStream = new FileInputStream(imageFile);
            byte[] imageData = new byte[(int) imageFile.length()];
            inputStream.read(imageData);

            preparedStatement.setBytes(1, imageData);
            preparedStatement.executeUpdate();

            System.out.println("Image stored successfully in the database.");

        } catch (SQLException e) {
            System.err.println("SQL Exception: " + e.getMessage());
        } catch (Exception e) {
            System.err.println("Exception: " + e.getMessage());
        }
    }
}
