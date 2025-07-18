import java.nio.file.Files;
import java.nio.file.Paths;
import static java.nio.file.StandardOpenOption.*;

public class Main {

    public static void main(String[] args) throws Exception {
        Files.write(Paths.get("important_config"), "Important information".getBytes(), CREATE, WRITE, TRUNCATE_EXISTING);
    }
}