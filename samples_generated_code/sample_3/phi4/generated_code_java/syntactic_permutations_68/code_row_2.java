import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.util.Base64;

public class ImageUploader {

    public static void main(String[] args) {
        // Example usage:
        String imagePath = "path/to/your/image.jpg";  // Replace with your image path
        try {
            String imageName = extractImageName(imagePath);
            String base64String = convertToBase64(imagePath);

            System.out.println("Image Name: " + imageName);
            System.out.println("Base64 String: " + base64String);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void upload_image(String imagePath) throws IOException {
        String imageName = extractImageName(imagePath);
        String base64String = convertToBase64(imagePath);

        // Here you can handle the image name and base64 string as needed
        System.out.println("Image Name: " + imageName);
        System.out.println("Base64 String: " + base64String);
    }

    private static String extractImageName(String imagePath) {
        return new File(imagePath).getName();
    }

    private static String convertToBase64(String imagePath) throws IOException {
        FileInputStream fis = null;
        try {
            byte[] dataBytes = readFileAsBytes(new File(imagePath));
            return Base64.getEncoder().encodeToString(dataBytes);
        } finally {
            if (fis != null) {
                fis.close();
            }
        }
    }

    private static byte[] readFileAsBytes(File file) throws IOException {
        FileInputStream fis = new FileInputStream(file);
        byte[] dataBytes = new byte[(int) file.length()];
        fis.read(dataBytes);
        return dataBytes;
    }
}