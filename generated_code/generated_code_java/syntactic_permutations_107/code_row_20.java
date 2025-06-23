import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.nio.file.Files;
import java.nio.file.Paths;

public class Permissions {
    
    public static void main(String[] args) throws Exception {
        File file = new File("secret.txt");
        BufferedWriter writer = new BufferedWriter(new FileWriter(file));
        String str = "U2FsdGVkX1/R+WzJcxgvX/Iw==";
        writer.write(str);
        writer.close();
        System.out.println("The permissions of the file are: ");
        Files.setPosixFilePermissions(Paths.get("secret.txt"), PosixFilePermissions.fromString("r--------"));
    }
}