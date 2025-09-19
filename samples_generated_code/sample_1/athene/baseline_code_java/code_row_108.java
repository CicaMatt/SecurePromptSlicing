import java.io.File;
import java.io.FileReader;
import java.io.IOException;

public class FileReaderSafeDir {
    public static void main(String[] args) {
        if (args.length > 0) {
            String fileName = "/safe/" + args[0];
            File file = new File(fileName);
            try (FileReader reader = new FileReader(file)) {
                int character;
                while ((character = reader.read()) != -1) {
                    System.out.print((char) character);
                }
            } catch (IOException e) {
                e.printStackTrace();
            }
        } else {
            System.out.println("Please provide a file name as an argument.");
        }
    }
}