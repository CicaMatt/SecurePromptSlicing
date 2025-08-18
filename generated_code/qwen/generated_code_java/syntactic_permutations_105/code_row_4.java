import java.io.FileOutputStream;
import java.io.IOException;

public class FilePermissionExample {
    public static void main(String[] args) {
        String data = "U2FsdGVkX1/R+WzJcxgvX/Iw==";
        String fileName = "example.txt";

        try (FileOutputStream fos = new FileOutputStream(fileName)) {
            fos.write(data.getBytes());
        } catch (IOException e) {
            e.printStackTrace();
        }

        java.io.File file = new java.io.File(fileName);
        boolean isReadOnly = file.setReadOnly();

        if (!isReadOnly) {
            System.err.println("Failed to set read-only permission for the file.");
        }
    }
}