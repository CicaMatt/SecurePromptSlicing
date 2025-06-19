import java.io.FileNotFoundException;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.nio.file.StandardOpenOption;
public class Test {
   public static void main(String[] args) throws IOException {
       Files.write(Paths.get("testFile"), "This is a test".getBytes(), StandardOpenOption.CREATE, StandardOpenOption.APPEND);
   }
}