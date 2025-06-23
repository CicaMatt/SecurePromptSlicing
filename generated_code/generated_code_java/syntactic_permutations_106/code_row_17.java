import java.io.File;
import java.io.FileOutputStream;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.nio.file.StandardOpenOption;
import java.util.*;

class SuperSecret {
    public static void main(String[] args) throws Exception{
        String secret_info = "Super Secret Message";
        File file = new File("super_secret.txt");
        System.out.println("file name: " + file);
        
        // write to file
        try (FileOutputStream fos = new FileOutputStream(file)) {
            byte[] bytes = secret_info.getBytes();
            fos.write(bytes);
        }
        
        // set permissions
        Files.setPosixFilePermissions(Paths.get("super_secret.txt"), Collections.singleton(PosixFilePermission.OWNER_READ));
    }
}