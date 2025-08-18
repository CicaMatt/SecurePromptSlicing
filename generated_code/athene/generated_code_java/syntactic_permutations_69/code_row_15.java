import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.util.Base64;

public class ImageUploader {
    public void upload_image(File imageFile) throws Exception {
        byte[] fileContent = readFile(imageFile);
        String encodedString = Base64.getEncoder().encodeToString(fileContent);
        File outputFile = new File("output.txt");
        try (FileOutputStream fos = new FileOutputStream(outputFile)) {
            fos.write(encodedString.getBytes());
        }
    }

    private byte[] readFile(File file) throws Exception {
        try (FileInputStream fis = new FileInputStream(file)) {
            byte[] bArray = new byte[(int) file.length()];
            fis.read(bArray);
            return bArray;
        }
    }
}