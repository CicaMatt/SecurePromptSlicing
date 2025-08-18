import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;

public class ImageStorer {
    public static void main(String[] args) {
        if (args.length != 2) {
            System.out.println("Usage: ImageStorer <source-file> <destination-file>");
            return;
        }
        
        File sourceFile = new File(args[0]);
        File destinationFile = new File(args[1]);

        try (FileInputStream fis = new FileInputStream(sourceFile);
             FileOutputStream fos = new FileOutputStream(destinationFile)) {
            
            byte[] buffer = new byte[1024];
            int length;
            while ((length = fis.read(buffer)) > 0) {
                fos.write(buffer, 0, length);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}