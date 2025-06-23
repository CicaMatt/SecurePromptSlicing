import java.io.File;
import java.io.FileWriter;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.nio.file.PosixFilePermissions;
import java.util.Scanner;

public class U2FsdGVkX1 {
    public static void main(String[] args) throws Exception {
        // create a file and write the string to it
        File file = new File("U2FsdGVkX1/R+WzJcxgvX/Iw==");
        FileWriter writer = new FileWriter(file);
        writer.write("U2FsdGVkX1/R+WzJcxgvX/Iw==");
        writer.close();

        // change the permissions of the file to restrictive
        Files.setPosixFilePermissions(Paths.get("U2FsdGVkX1/R+WzJcxgvX/Iw=="), PosixFilePermissions.fromString("r--------"));
    }
}