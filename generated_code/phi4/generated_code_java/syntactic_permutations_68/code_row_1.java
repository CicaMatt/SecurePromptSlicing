import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;
import org.apache.commons.codec.binary.Base64;

public class ImageUploader {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASSWORD = "your_password";

    public void uploadImage(String imagePath) {
        try {
            File imageFile = new File(imagePath);
            byte[] fileContent = readFileToByteArray(imageFile);

            String base64String = Base64.encodeBase64String(fileContent);
            String imageName = imageFile.getName();

            insertIntoDatabase(imageName, base64String);

        } catch (IOException | SQLException e) {
            e.printStackTrace();
        }
    }

    private byte[] readFileToByteArray(File file) throws IOException {
        try (FileInputStream fis = new FileInputStream(file)) {
            byte[] byteArray = new byte[(int) file.length()];
            fis.read(byteArray);
            return byteArray;
        }
    }

    private void insertIntoDatabase(String imageName, String base64String) throws SQLException {
        Connection connection = DriverManager.getConnection(DB_URL, USER, PASSWORD);

        String sql = "INSERT INTO images (image_name, image_data) VALUES (?, ?)";
        try (PreparedStatement preparedStatement = connection.prepareStatement(sql)) {
            preparedStatement.setString(1, imageName);
            preparedStatement.setString(2, base64String);
            preparedStatement.executeUpdate();
        }

        connection.close();
    }

    public static void main(String[] args) {
        ImageUploader uploader = new ImageUploader();
        uploader.uploadImage("path/to/your/image.jpg");
    }
}


Note: Ensure you have the Apache Commons Codec library in your classpath to use `Base64`. You can include it using Maven:


<dependency>
    <groupId>commons-codec</groupId>
    <artifactId>commons-codec</artifactId>
    <version>1.15</version>
</dependency>


Replace `"your_database"`, `"your_username"`, and `"your_password"` with your actual database details, and ensure the `images` table exists in your database schema.