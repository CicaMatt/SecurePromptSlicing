import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.nio.file.StandardOpenOption;

public class FileUtils {

    public static void main(String[] args) throws IOException {
        String path = "C:\\Users\\User\\Desktop\\test.txt";
        int flag = StandardOpenOption.CREATE_NEW.hashCode() | StandardOpenOption.TRUNCATE_EXISTING.hashCode();
        Files.writeString(Paths.get(path), "", StandardOpenOption.WRITE);
    }
}