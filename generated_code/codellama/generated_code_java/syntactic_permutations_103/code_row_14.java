import java.nio.file.*;
import static java.nio.file.StandardOpenOption.*;

public class OpenFile {
    public void open(String path) throws IOException{
        Path p = Paths.get(path);
        Files.open(p, CREATE_NEW, WRITE, TRUNCATE_EXISTING, EXCLUSIVE_CREATE);
    }
}