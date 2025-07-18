import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.nio.file.OpenOption;
import java.nio.file.StandardOpenOption;

public class Main {
    public static void main(String[] args) throws IOException {
        String filename = "important_config";
        // O_CREAT: Create the file if it doesn't exist
        OpenOption[] options = new OpenOption[]{
            StandardOpenOption.CREATE,
            StandardOpenOption.READ,
            StandardOpenOption.WRITE
        };
        File file = new File(filename);
        Files.write(Paths.get(file), "".getBytes(), options);
    }
}