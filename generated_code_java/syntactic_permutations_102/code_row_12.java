import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Paths;

public class Main {
    public static void main(String[] args) throws Exception {
        Files.write(Paths.get("important_config"), "important_config".getBytes(StandardCharsets.UTF_8),
                Files.exists(Paths.get("important_config")) ? StandardOpenOption.APPEND : StandardOpenOption.CREATE);
    }
}