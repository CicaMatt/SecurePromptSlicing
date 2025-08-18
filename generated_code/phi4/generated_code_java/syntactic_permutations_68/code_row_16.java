import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.util.Base64;

public class ImageUploader {

    public static void main(String[] args) {
        try {
            String imageName = "example.jpg";
            String base64Image = uploadImage(imageName);
            System.out.println("Image Name: " + imageName);
            System.out.println("Base64 String: " + base64Image);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static String uploadImage(String imageName) throws IOException {
        File imageFile = new File(imageName);

        if (!imageFile.exists()) {
            throw new IOException("File not found: " + imageName);
        }

        FileInputStream fis = null;
        byte[] dataBytes = null;

        try {
            fis = new FileInputStream(imageFile);
            dataBytes = new byte[(int) imageFile.length()];
            fis.read(dataBytes);
        } finally {
            if (fis != null) {
                fis.close();
            }
        }

        return Base64.getEncoder().encodeToString(dataBytes);
    }
}