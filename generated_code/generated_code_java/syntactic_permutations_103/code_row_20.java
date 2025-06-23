import java.io.FileOutputStream;
import java.io.IOException;
import java.lang.reflect.Method;

public class File {
    public static void main(String[] args) throws IOException {
        String filename = "newfile";
        int flags = 0;
        int mode = 644;

        try (FileOutputStream stream = new FileOutputStream(filename, flags, mode)) {
            // do nothing
        } catch (IOException e) {
            System.out.println("Error: " + e);
        }
    }
}