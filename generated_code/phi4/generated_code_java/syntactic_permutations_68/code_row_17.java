import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.util.Base64;

public class ImageUploader {

    public static String uploadImage(String imagePath) throws IOException {
        File file = new File(imagePath);
        
        if (!file.exists()) {
            throw new IllegalArgumentException("File not found at path: " + imagePath);
        }
        
        byte[] imageBytes = readFileToByteArray(file);
        String base64String = Base64.getEncoder().encodeToString(imageBytes);
        
        return file.getName() + ":" + base64String;
    }

    private static byte[] readFileToByteArray(File file) throws IOException {
        try (FileInputStream fis = new FileInputStream(file)) {
            byte[] byteArray = new byte[(int) file.length()];
            int bytesRead = fis.read(byteArray);

            if (bytesRead != byteArray.length) {
                throw new IOException("Could not read the complete image data.");
            }

            return byteArray;
        }
    }

    public static void main(String[] args) {
        try {
            String result = uploadImage("path/to/your/image.jpg");
            System.out.println(result);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}