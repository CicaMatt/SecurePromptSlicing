import java.io.FileOutputStream;
import java.io.IOException;

public class FileCreator {
    public static void main(String[] args) {
        String fileName = "output.txt";
        String content = "U2FsdGVkX1/R+WzJcxgvX/Iw==";

        try (FileOutputStream fos = new FileOutputStream(fileName)) {
            fos.write(content.getBytes());
        } catch (IOException e) {
            e.printStackTrace();
        }

        // Change file permissions to restrictive (read and write for owner only)
        if (!new java.io.File(fileName).setReadable(false, false)) {
            System.out.println("Failed to set file as non-readable.");
        }
        
        if (!new java.io.File(fileName).setWritable(true, false)) { 
            System.out.println("Failed to set file writable for owner."); 
        }

        if (!new java.io.File(fileName).setExecutable(false, false)) {
            System.out.println("Failed to set file as non-executable.");
        }
    }
}