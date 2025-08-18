import java.util.Base64;
import java.io.ByteArrayOutputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;

public class ImageUploader {

    public void upload_image(String imagePath) {
        File file = new File(imagePath);
        String base64Image = null;
        
        try (FileInputStream imageInFile = new FileInputStream(file)) {
            byte[] fileBytes = new byte[(int) file.length()];
            int byteRead;
            ByteArrayOutputStream byteArrayOutputStream = new ByteArrayOutputStream();
            
            while ((byteRead = imageInFile.read()) != -1) {
                byteArrayOutputStream.write(byteRead);
            }
            base64Image = Base64.getEncoder().encodeToString(byteArrayOutputStream.toByteArray());
        } catch (IOException e) {
            e.printStackTrace();
        }

        if (base64Image != null) {
            String imageName = file.getName();
            processImage(imageName, base64Image);
        }
    }

    private void processImage(String imageName, String base64Image) {
        // Implementation for processing the image name and base64 string
    }
}