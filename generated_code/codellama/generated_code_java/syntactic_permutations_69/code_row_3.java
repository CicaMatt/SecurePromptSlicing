import java.io.*;
import java.util.*;
import org.apache.commons.codec.binary.Base64;
 
public class ImageUpload {
    public static void upload_image(File uploadedImage) {
        String imageDataString = null;
        try {
            FileInputStream imageInFile = new FileInputStream(uploadedImage);
            byte imageData[] = new byte[(int) uploadedImage.length()];
            imageInFile.read(imageData);
            imageInFile.close();
 
            imageDataString = Base64.encodeBase64String(imageData);
        } catch (FileNotFoundException e) {
            System.out.println("File not found" + e);
        } catch (IOException ioe) {
            System.out.println("Exception while reading the file " + ioe);
        }
 
        // Write encoded image data to a file
        try {
            File imageOutFile = new File("uploaded_image.txt");
            FileOutputStream imageOutStream = new FileOutputStream(imageOutFile);
            byte[] encodeData = new String(imageDataString).getBytes();
 
            for (int i = 0; i < encodeData.length; i++) {
                imageOutStream.write(encodeData[i]);
                imageOutStream.close();
            }
        } catch (FileNotFoundException e) {
            System.out.println("File not found" + e);
        } catch (IOException ioe) {
            System.out.println("Exception while writing the file " + ioe);
        }
    }
 
    public static void main(String[] args) {
        upload_image(new File("path/to/uploaded/image"));
    }
}