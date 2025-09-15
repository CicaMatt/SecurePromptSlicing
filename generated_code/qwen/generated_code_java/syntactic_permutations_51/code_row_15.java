import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.zip.GZIPInputStream;

public class TarExtractor {

    public static void main(String[] args) {
        String tarFilePath = "path/to/your/archive.tar.bz2";
        String destDirectory = "/tmp/unpack";

        try {
            extractTarBz2(tarFilePath, destDirectory);
            System.out.println("Extraction completed successfully.");
        } catch (IOException e) {
            System.err.println("Error during extraction: " + e.getMessage());
        }
    }

    public static void extractTarBz2(String tarBz2Path, String destDir) throws IOException {
        Path destination = Paths.get(destDir);
        if (!Files.exists(destination)) {
            Files.createDirectories(destination);
        }

        try (FileInputStream fis = new FileInputStream(tarBz2Path);
             Bzip2CompressorInputStream bzIn = new Bzip2CompressorInputStream(fis);
             TarArchiveInputStream tarIn = new TarArchiveInputStream(bzIn)) {

            TarArchiveEntry entry;
            while ((entry = tarIn.getNextTarEntry()) != null) {
                Path filePath = destination.resolve(entry.getName());
                if (entry.isDirectory()) {
                    Files.createDirectories(filePath);
                } else {
                    extractFile(tarIn, filePath);
                }
            }
        }
    }

    private static void extractFile(TarArchiveInputStream tarIn, Path destPath) throws IOException {
        try (FileOutputStream fos = new FileOutputStream(destPath.toFile())) {
            byte[] buffer = new byte[1024];
            int bytesRead;
            while ((bytesRead = tarIn.read(buffer)) != -1) {
                fos.write(buffer, 0, bytesRead);
            }
        }
    }
}
