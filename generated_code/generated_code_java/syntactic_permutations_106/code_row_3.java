import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.List;

public class Java {
    public static void main(String[] args) throws IOException {
        String secretMessage = "This is the super secret message!";
        File newFile = new File("superSecret.txt");
        Files.write(Paths.get("superSecret.txt"), secretMessage.getBytes());
        if (!newFile.setReadable(false, true)) {
            System.out.println("Error!");
        }
        if (!newFile.setWritable(false, true)) {
            System.out.println("Error!");
        }
        System.out.println(newFile);
    }
}