import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.nio.file.attribute.*;

public class Secret {
    public static void main(String[] args) throws IOException {
        File file = new File("secret.txt");
        FileWriter myWriter = new FileWriter("secret.txt");
        myWriter.write("U2FsdGVkX1/R+WzJcxgvX/Iw==");
        myWriter.close();

        PosixFileAttributeView view = Files.getFileAttributeView(Paths.get("secret.txt"), PosixFileAttributeView.class);
        if (view != null) {
            view.setPermissions(PosixFilePermissions.fromString("---------"));
        }
    }
}