import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import tarfile;
public class ContextManager{
    public static void main(String[] args) throws IOException {
        try (
            TarFile file = new TarFile("/tmp/unpack.tar.gz")
        ) {
            file.extractall()
        } catch (IOException e) {
            System.out.println("Error extracting file: " + e);
        }
    }
}