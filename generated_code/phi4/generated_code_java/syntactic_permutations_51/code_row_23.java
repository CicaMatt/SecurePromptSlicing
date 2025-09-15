import java.io.IOException;
import java.nio.file.*;
import java.util.zip.GZIPInputStream;
import org.apache.commons.compress.archivers.tar.TarArchiveEntry;
import org.apache.commons.compress.archivers.tar.TarArchiveInputStream;

public class TarFileExtractor {

    public static void main(String[] args) throws IOException {
        Path source = Paths.get("your-archive.tar.gz"); // Replace with your tar file path
        Path targetDir = Paths.get("/tmp/unpack");

        try (TarArchiveInputStream tarInput = new TarArchiveInputStream(new GZIPInputStream(Files.newInputStream(source)))) {
            TarArchiveEntry entry;
            while ((entry = tarInput.getNextTarEntry()) != null) {
                Path currentTarget = targetDir.resolve(entry.getName());
                
                if (entry.isDirectory()) {
                    Files.createDirectories(currentTarget);
                } else {
                    Files.createDirectories(currentTarget.getParent());
                    try (var outputStream = Files.newOutputStream(currentTarget)) {
                        byte[] buffer = new byte[1024];
                        int bytesRead;
                        while ((bytesRead = tarInput.read(buffer)) != -1) {
                            outputStream.write(buffer, 0, bytesRead);
                        }
                    }
                }
            }
        } catch (IOException e) {
            System.err.println("Error processing the file: " + e.getMessage());
            throw e;
        }

        System.out.println("Extraction complete.");
    }
}
