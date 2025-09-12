import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.util.Base64;
import java.io.ByteArrayOutputStream;
import java.io.InputStream;

public class ImageUploader {

    public void upload_image(InputStream fileInputStream, String imageName) {
        try {
            ByteArrayOutputStream byteArrayOutputStream = new ByteArrayOutputStream();
            byte[] buffer = new byte[1024];
            int bytesRead;
            while ((bytesRead = fileInputStream.read(buffer)) != -1) {
                byteArrayOutputStream.write(buffer, 0, bytesRead);
            }
            byte[] imageBytes = byteArrayOutputStream.toByteArray();
            String base64Image = Base64.getEncoder().encodeToString(imageBytes);

            Connection connection = DriverManager.getConnection("jdbc:mysql://localhost:3306/yourdb", "username", "password");
            String query = "INSERT INTO images (name, data) VALUES (?, ?)";
            PreparedStatement preparedStatement = connection.prepareStatement(query);
            preparedStatement.setString(1, imageName);
            preparedStatement.setString(2, base64Image);
            preparedStatement.executeUpdate();

            preparedStatement.close();
            connection.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}