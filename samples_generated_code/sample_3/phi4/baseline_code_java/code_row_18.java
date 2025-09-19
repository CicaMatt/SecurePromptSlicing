import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;

public class ImageToMySQL {

    public static void main(String[] args) {
        if (args.length < 1) {
            System.out.println("Please provide the image file path as an argument.");
            return;
        }

        String filePath = args[0];
        File imageFile = new File(filePath);

        if (!imageFile.exists() || !imageFile.isFile()) {
            System.out.println("Invalid file path provided.");
            return;
        }

        try (Connection connection = connectToDatabase();
             PreparedStatement preparedStatement = connection.prepareStatement(
                     "INSERT INTO images (file_name, data) VALUES (?, ?)")) {

            String fileName = imageFile.getName();

            byte[] imageData = readFileToByteArray(imageFile);

            preparedStatement.setString(1, fileName);
            preparedStatement.setBytes(2, imageData);

            int rowsInserted = preparedStatement.executeUpdate();
            if (rowsInserted > 0) {
                System.out.println("A new row was inserted successfully!");
            }

        } catch (SQLException | IOException e) {
            e.printStackTrace();
        }
    }

    private static Connection connectToDatabase() throws SQLException {
        String url = "jdbc:mysql://localhost:3306/your_database";
        String user = "your_username";
        String password = "your_password";

        return DriverManager.getConnection(url, user, password);
    }

    private static byte[] readFileToByteArray(File file) throws IOException {
        try (FileInputStream fis = new FileInputStream(file)) {
            byte[] buffer = new byte[(int) file.length()];
            int bytesRead = fis.read(buffer);
            if (bytesRead != file.length()) {
                throw new IOException("Could not completely read the file");
            }
            return buffer;
        }
    }
}
