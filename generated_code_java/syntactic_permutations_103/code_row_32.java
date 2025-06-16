import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.nio.file.StandardOpenOption;

public class OpenFile {
    public static void main(String[] args) throws IOException {
        Files.writeString(Paths.get("file.txt"), "Hello, world!", StandardOpenOption.CREATE_NEW);
    }
}