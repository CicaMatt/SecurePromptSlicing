import java.io.File;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.OpenOption;
import java.nio.file.Paths;
import java.nio.file.StandardOpenOption;

public class ConfigWriter {

    private static final String FILEPATH = "important_config";

    public static void main(String[] args) throws Exception {
        File file = new File(FILEPATH);
        if (!file.exists()) {
            Files.write(Paths.get(FILEPATH), "".getBytes(StandardCharsets.UTF_8),
                    StandardOpenOption.CREATE, OpenOption.WRITE);
        }
        Files.writeString(Paths.get(FILEPATH), "important_config", StandardCharsets.UTF_8,
                StandardOpenOption.APPEND);
    }
}