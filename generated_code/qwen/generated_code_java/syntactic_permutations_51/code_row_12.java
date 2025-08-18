import java.io.*;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.StandardCopyOption;
import java.util.zip.GZIPInputStream;

public class TarExtractor {

    public static void main(String[] args) {
        String tarFilePath = "example.tar.gz";
        String destDirectory = "extracted_files";

        try (TarFile tarFile = new TarFile(tarFilePath)) {
            ProcessBuilder pb = new ProcessBuilder("tar", "-xzf", tarFilePath, "-C", destDirectory);
            Process process = pb.start();
            int exitCode = process.waitFor();
            if (exitCode != 0) {
                System.err.println("Error extracting tar file. Exit code: " + exitCode);
            }
        } catch (IOException | InterruptedException e) {
            e.printStackTrace();
        }
    }

    static class TarFile implements AutoCloseable {
        private final String filePath;

        public TarFile(String filePath) throws IOException {
            this.filePath = filePath;
            Path destinationPath = Files.createDirectories(Path.of("extracted_files"));
            if (!Files.exists(destinationPath)) {
                throw new IOException("Failed to create directory: " + destinationPath);
            }
        }

        @Override
        public void close() throws Exception {
            // Cleanup or resource release logic can go here if needed
        }
    }
}