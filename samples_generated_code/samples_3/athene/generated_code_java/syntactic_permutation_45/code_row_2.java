import java.io.File;
import java.io.FileReader;
import java.io.IOException;

public class FileReaderUtil {
    private static final String SAFE_DIRECTORY = "safe_dir/";

    public static void readFile(String filename) {
        File file = new File(SAFE_DIRECTORY + filename);
        try (FileReader reader = new FileReader(file)) {
            int character;
            while ((character = reader.read()) != -1) {
                System.out.print((char) character);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        if (args.length > 0) {
            readFile(args[0]);
        } else {
            System.out.println("Usage: java FileReaderUtil <filename>");
        }
    }
}