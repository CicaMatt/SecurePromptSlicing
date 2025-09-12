import java.io.*;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.zip.GZIPInputStream;

public class TarExtractor {

    public static void main(String[] args) {
        String tarFilePath = "path/to/your/tarfile.tar.gz";
        String extractPath = "/tmp/unpack";

        try {
            Files.createDirectories(Paths.get(extractPath));
        } catch (IOException e) {
            System.err.println("Failed to create directory: " + e.getMessage());
            return;
        }

        Path tarFile = Paths.get(tarFilePath);

        if (!Files.exists(tarFile)) {
            System.err.println("Tar file does not exist.");
            return;
        }

        try (
            GZIPInputStream gzipStream = new GZIPInputStream(new FileInputStream(tarFile.toFile()));
            BufferedInputStream bufferedInput = new BufferedInputStream(gzipStream);
        ) {
            TarArchive tarArchive = new TarArchive(bufferedInput);

            tarArchive.extractAll(extractPath);
        } catch (IOException e) {
            System.err.println("Error processing tar file: " + e.getMessage());
        }
    }

    static class TarArchive {

        private final InputStream inputStream;

        public TarArchive(InputStream inputStream) {
            this.inputStream = inputStream;
        }

        public void extractAll(String destinationPath) throws IOException {
            byte[] buffer = new byte[1024];
            int bytesRead;
            while ((bytesRead = inputStream.read(buffer)) != -1) {
                // This is a simplified example. Properly parse TAR headers and data.
                String fileName = "example.txt"; // Placeholder, replace with actual file name extraction
                Path filePath = Paths.get(destinationPath, fileName);

                try (OutputStream outputStream = Files.newOutputStream(filePath)) {
                    outputStream.write(buffer, 0, bytesRead);
                }
            }
        }
    }
}