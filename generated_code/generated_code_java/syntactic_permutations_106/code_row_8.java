import java.io.*;
import java.nio.file.Files;
import java.nio.file.Paths;
import static java.nio.file.StandardCopyOption.*;

public class Secret {
    public static void main(String[] args) throws IOException {
        String superSecret = "Hello, this is a super secret message";
        File file = new File("secretFile");
        Files.writeString(Paths.get(file), superSecret);
        setReadOnly(file);
        System.out.println(file.getName());
    }
}