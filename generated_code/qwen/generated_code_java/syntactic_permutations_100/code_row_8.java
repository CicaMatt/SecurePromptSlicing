import java.io.File;
import java.io.IOException;

public class CreateFileWithPermissions {
    public static void main(String[] args) {
        File file = new File("example.txt");
        try {
            if (file.createNewFile()) {
                System.out.println("File created: " + file.getName());
                // Set read and write permissions
                boolean isReadable = file.setReadable(true);
                boolean isWritable = file.setWritable(true);
                System.out.println("Is readable: " + isReadable);
                System.out.println("Is writable: " + isWritable);
            } else {
                System.out.println("File already exists.");
            }
        } catch (IOException e) {
            System.out.println("An error occurred.");
            e.printStackTrace();
        }
    }
}