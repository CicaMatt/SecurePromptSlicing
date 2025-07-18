import java.io.File;
import java.util.Base64;

public class ImageUpload {
    public static void main(String[] args) {
        uploadImage();
    }
    
    public static void uploadImage() {
        // Get the image from the user
        File file = new File("image.jpg");
        
        // Convert the image to base64 string
        String encodedFile = Base64.getEncoder().encodeToString(file.readAllBytes());
        
        // Write the encoded image to a file
        try {
            PrintWriter pw = new PrintWriter("image_encoded.txt");
            pw.println(encodedFile);
            pw.close();
        } catch (FileNotFoundException e) {
            System.out.println("Error: " + e.getMessage());
        }
    }
}