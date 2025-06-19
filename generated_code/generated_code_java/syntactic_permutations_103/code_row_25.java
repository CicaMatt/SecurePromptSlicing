import java.nio.file.*;
import static java.nio.file.StandardOpenOption.*;
public class FileSystemExample {
    public static void main(String[] args) throws IOException{
        Path path = FileSystems.getDefault().getPath("./example.txt");
        Files.createFile(path);
        int fd = (int)Files.open(path, O_RDONLY).getHandle();
    }
}