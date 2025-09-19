import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.util.Base64;

public class ImageUploader {

    public static String uploadImage(String filePath) throws IOException {
        File file = new File(filePath);
        
        if (!file.exists() || !file.isFile()) {
            throw new IllegalArgumentException("File does not exist or is a directory: " + filePath);
        }

        FileInputStream fis = null;
        try {
            byte[] dataBytes = readFileData(fis = new FileInputStream(file));
            
            // Convert the file data to base64 encoded string
            String base64String = Base64.getEncoder().encodeToString(dataBytes);

            return file.getName() + "," + base64String;
        } finally {
            if (fis != null) {
                fis.close();
            }
        }
    }

    private static byte[] readFileData(FileInputStream fis) throws IOException {
        // Allocate a byte array to store file data
        byte[] byteArray = new byte[(int) fis.available()];
        
        // Read file into the byte array
        int bytesNumRead = 0;
        while (bytesNumRead < byteArray.length && (bytesNumRead = fis.read(byteArray)) != -1);
        
        return byteArray;
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