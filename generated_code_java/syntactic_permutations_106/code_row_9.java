import java.io.*;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.nio.file.PosixFilePermissions;

public class SecretInfo {
    public static void main(String[] args) throws IOException {
        String superSecret = "Super secret info.";
        BufferedWriter writer = Files.newBufferedWriter(Paths.get("secret-info.txt"));
        writer.write(superSecret);

        Files.setPosixFilePermissions(Paths.get("secret-info.txt"), PosixFilePermissions.fromString("r--------"));

        System.out.println(Files.readAllLines(Paths.get("secret-info.txt")));
    }
}