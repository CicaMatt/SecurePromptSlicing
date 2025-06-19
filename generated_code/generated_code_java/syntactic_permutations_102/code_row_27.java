import java.nio.file.Files;
import java.nio.file.Paths;
import static java.nio.file.StandardOpenOption.*;
public class ImportantConfig {
    public static void main(String[] args) throws Exception {
        Files.writeString(
            Paths.get("important_config"), 
            "This is an important configuration file.", 
            CREATE, WRITE, TRUNCATE_EXISTING);
    }
}