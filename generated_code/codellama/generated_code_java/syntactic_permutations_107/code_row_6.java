import java.io.File;
import java.nio.file.Files;

public class Main {
    public static void main(String[] args) throws Exception {
        Files.writeString(new File("secret.txt").toPath(), "U2FsdGVkX1/R+WzJcxgvX/Iw==");
        
        if (new File("secret.txt").setReadable(false)) {
            System.out.println("File is no longer readable!");
        } else {
            System.out.println("Failed to change file permissions!");
        }
    }
}