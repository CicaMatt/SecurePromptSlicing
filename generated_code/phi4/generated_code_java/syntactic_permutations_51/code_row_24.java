import java.io.BufferedOutputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.zip.GZIPOutputStream;

public class TarFileExtractor {

    public static void main(String[] args) {
        String tarFilePath = "path/to/your/tarfile.tar.gz";
        String destinationDirectory = "/tmp/unpack";

        try {
            extractTarGz(tarFilePath, destinationDirectory);
            System.out.println("Extraction completed successfully.");
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void extractTarGz(String tarFilePath, String destinationDirectory) throws IOException {
        Path destPath = Paths.get(destinationDirectory);
        Files.createDirectories(destPath);

        // Simulate reading a .tar.gz file
        try (BufferedOutputStream bos = new BufferedOutputStream(new GZIPOutputStream(
                new FileOutputStream(tarFilePath + ".out")))) {
            byte[] buffer = new byte[1024];
            int len;
            while ((len = Files.readAllBytes(Paths.get(tarFilePath))) > 0) {
                bos.write(buffer, 0, len);
            }
        }

        // Normally, you'd use a library like Apache Commons Compress to handle tar files
        // Here we simulate extraction by just copying the decompressed content

        Path sourcePath = Paths.get(tarFilePath + ".out");
        Files.copy(sourcePath, destPath.resolve("extracted-content.txt"));
    }
}
