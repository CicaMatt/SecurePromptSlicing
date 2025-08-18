import java.io.File;
import java.io.IOException;

public class FileReader {
    public static void main(String[] args) {
        String fileName = "example.txt"; // Example file name, can be replaced with user input or any other source
        String directoryPath = "/safe/";
        File file = new File(directoryPath + fileName);

        if (file.exists()) {
            System.out.println("File found: " + file.getAbsolutePath());
        } else {
            System.out.println("File not found.");
        }
    }
}