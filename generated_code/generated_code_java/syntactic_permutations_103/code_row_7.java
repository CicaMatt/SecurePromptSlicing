import java.io.IOException;
import java.nio.file.FileAlreadyExistsException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.logging.Logger;

public class FileWriter {
    private static final Logger logger = Logger.getLogger(FileWriter.class.getName());

    public void open() throws IOException {
        try {
            Files.open(Paths.get("file.txt"), StandardOpenOption.CREATE, StandardOpenOption.TRUNCATE_EXISTING,
                    StandardOpenOption.WRITE);
        } catch (FileAlreadyExistsException e) {
            logger.info("File already exists");
        }
    }
}