import java.io.FileOutputStream;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.Arrays;
public class MySecret {
    public static void main(String[] args) throws Exception {
        String secret = "I'm super secret!";
        Files.writeString(Paths.get("secret_info.txt"), secret);
        System.out.println("Wrote file to: " + new FileOutputStream("secret_info.txt").getFD().toString());
    }
}