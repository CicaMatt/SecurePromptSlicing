import java.io.*;
import java.nio.file.*;
import static java.nio.file.StandardOpenOption.*;
public class open {
    public static void main(String[] args) throws IOException {
        Path myFile = Paths.get("/path/to/myfile");
        Files.open(myFile, CREATE_NEW, WRITE, TRUNCATE_EXISTING, EXCLUSIVE_CREATE);
    }
}