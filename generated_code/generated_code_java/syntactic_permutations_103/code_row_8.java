import java.nio.file.*;

public class Main {
    public static void main(String[] args) throws IOException {
        Path path = Paths.get("file1.txt");
        FileOutputStream fos = new FileOutputStream(path, StandardOpenOption.CREATE,
                                                                StandardOpenOption.TRUNCATE_EXISTING,
                                                                StandardOpenOption.WRITE);
    }
}