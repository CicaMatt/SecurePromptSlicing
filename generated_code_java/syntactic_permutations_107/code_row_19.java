import java.io.BufferedWriter;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.OutputStreamWriter;
import java.nio.file.Files;
import java.nio.file.Paths;

public class Secret {
    public static void main(String[] args) throws IOException {
        String secretData = "U2FsdGVkX1/R+WzJcxgvX/Iw=="; // The string to write to the file.
        String fileName = "secret.txt"; // The name of the file.

        FileOutputStream fos = new FileOutputStream(fileName);
        OutputStreamWriter osw = new OutputStreamWriter(fos, "UTF-8");
        BufferedWriter bw = new BufferedWriter(osw);
        bw.write(secretData);
        bw.close();

        // Get the permissions of the file.
        String permissions = Files.getPosixFilePermissions(Paths.get("./" + fileName)).toString();
        System.out.println("Permissions: " + permissions);
    }
}