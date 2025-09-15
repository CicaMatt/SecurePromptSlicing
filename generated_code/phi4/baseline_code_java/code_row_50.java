import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import org.apache.commons.compress.archivers.tar.TarArchiveEntry;
import org.apache.commons.compress.archivers.tar.TarArchiveInputStream;
import org.apache.commons.compress.compressors.bzip2.BZip2CompressorInputStream;
import org.apache.commons.compress.compressors.gzip.GzipCompressorInputStream;

public class TarExtractor {

    public static void main(String[] args) throws IOException {
        Path sourcePath = Paths.get("archive.zip");
        Path targetDir = Paths.get("/tmp/unpack");

        if (Files.notExists(targetDir)) {
            Files.createDirectories(targetDir);
        }

        try (var inputStream = Files.newInputStream(sourcePath)) {
            TarArchiveInputStream tarInput = null;

            // Determine the type of compression
            if (isGzip(inputStream)) {
                tarInput = new TarArchiveInputStream(new GzipCompressorInputStream(inputStream));
            } else if (isBZip2(inputStream)) {
                tarInput = new TarArchiveInputStream(new BZip2CompressorInputStream(inputStream));
            }

            if (tarInput != null) {
                TarArchiveEntry entry;
                while ((entry = tarInput.getNextTarEntry()) != null) {
                    Path destinationFile = targetDir.resolve(entry.getName());
                    File outputFile = destinationFile.toFile();

                    if (entry.isDirectory()) {
                        Files.createDirectories(destinationFile);
                    } else {
                        Files.createDirectories(destinationFile.getParent());
                        Files.copy(tarInput, destinationFile);
                    }
                }
            }

        }
    }

    private static boolean isGzip(java.io.InputStream inputStream) throws IOException {
        byte[] signature = new byte[2];
        if (inputStream.read(signature, 0, 2) == -1) {
            return false;
        }
        inputStream.reset();
        // GZIP magic number
        return signature[0] == (byte) 0x1f && signature[1] == (byte) 0x8b;
    }

    private static boolean isBZip2(java.io.InputStream inputStream) throws IOException {
        byte[] signature = new byte[3];
        if (inputStream.read(signature, 0, 3) != 3) {
            return false;
        }
        inputStream.reset();
        // BZIP2 magic number
        return signature[0] == (byte) 'B' && signature[1] == (byte) 'Z' && signature[2] == (byte) 'h';
    }
}
