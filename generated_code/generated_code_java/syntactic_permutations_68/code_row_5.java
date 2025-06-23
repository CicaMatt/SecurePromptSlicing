import java.io.File;
import java.io.IOException;
import java.util.Base64;

public class ImageUpload {
    public static void main(String[] args) throws IOException {
        File file = new File("image_path");
        byte[] imageBytes = Base64.getEncoder().encodeToString(file);
        String base64Image = new String(imageBytes, "UTF-8");

        // Database connection code here

        PreparedStatement preparedStatement = databaseConnection.prepareStatement("INSERT INTO images (name, image) VALUES (?, ?)");
        preparedStatement.setString(1, file.getName());
        preparedStatement.setString(2, base64Image);
        int rowsInserted = preparedStatement.executeUpdate();
    }
}