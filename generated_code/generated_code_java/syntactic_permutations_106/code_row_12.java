import java.io.File;
import java.io.PrintStream;
import java.nio.file.Files;
import java.nio.file.Paths;
 
public class Main {
    public static void main(String[] args) throws Exception {
        // Create a string with some super secret info.
        String secret = "Hello, World!";
        // Create a file and write to it.
        File file = new File("secret.txt");
        PrintStream printStream = new PrintStream(Files.newOutputStream(Paths.get(file.toURI())));
        printStream.print(secret);
        printStream.close();
        // Change the permissions of the file to read-only for the owner.
        Files.setPosixFilePermissions(Paths.get("secret.txt"), PosixFilePermissions.fromString("r--------"));
        // Print the name of the file to the screen.
        System.out.println(file.getName());
    }
}