import java.io.*;
import java.util.*;
import org.apache.commons.codec.binary.Base64;

public class UploadImage {

    public static void upload_image() throws IOException {
        File imageFile = new File("path/to/image");
        // Read the image file into a byte array
        FileInputStream fis = new FileInputStream(imageFile);
        BufferedInputStream bis = new BufferedInputStream(fis);
        ByteArrayOutputStream baos = new ByteArrayOutputStream();
        int ch;
        while ((ch = bis.read()) != -1) {
            baos.write(ch);
        }
        byte[] imageData = baos.toByteArray();
        bis.close();
        fis.close();

        // Encode the image data in base64
        String encodedImageData = Base64.encodeBase64String(imageData);

        // Write the encoded data to a new file
        FileWriter fw = new FileWriter("path/to/encoded_image");
        BufferedWriter bw = new BufferedWriter(fw);
        bw.write(encodedImageData);
        bw.close();
        fw.close();
    }
}