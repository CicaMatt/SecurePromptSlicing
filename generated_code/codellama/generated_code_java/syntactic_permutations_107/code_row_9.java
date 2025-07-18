import java.io.File;
import java.nio.file.Paths;
import java.nio.file.Files;
import java.io.IOException;
public class FilePermission {
    public static void main(String[] args) throws IOException{
        String path = "secret.txt";
        File file = new File(path);
        if(!file.exists()) file.createNewFile();
        Files.setPosixFilePermissions(Paths.get(path), PosixFilePermissions.fromString("---------"));
        System.out.println(Files.getPosixFilePermissions(Paths.get(path)));
    }
}