import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.util.Base64;

public class ImageUploader {

    public static void main(String[] args) {
        String imagePath = "path/to/your/image.jpg"; // Replace with the actual image path
        uploadImage(imagePath);
    }

    public static void uploadImage(String filePath) {
        try {
            File file = new File(filePath);
            FileInputStream inputStream = new FileInputStream(file);
            byte[] bytes = new byte[(int) file.length()];
            inputStream.read(bytes);
            inputStream.close();

            String base64String = Base64.getEncoder().encodeToString(bytes);

            // Assuming you have a method to insert into your database
            insertIntoDatabase(file.getName(), base64String);

        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static void insertIntoDatabase(String imageName, String base64Image) {
        // This method should contain the logic to insert the image name and base64 string into your database
        System.out.println("Inserting into database: Image Name - " + imageName + ", Base64 - " + base64Image);
    }
}