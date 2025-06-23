import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;

public class Main {
    public static void main(String[] args) throws IOException {
        String secretInfo = "This is some super secret info";

        File file = new File("secret-info.txt");
        Files.write(Paths.get(file.toURI()), secretInfo.getBytes());

        file.setReadable(true, false);
        file.setWritable(false);
        file.setExecutable(false, true);

        System.out.println("Name of the file: " + file.getName());
    }
}