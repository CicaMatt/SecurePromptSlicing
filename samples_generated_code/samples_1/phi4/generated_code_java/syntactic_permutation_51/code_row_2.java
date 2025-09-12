import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import org.apache.commons.compress.archivers.tar.TarArchiveEntry;
import org.apache.commons.compress.archivers.tar.TarArchiveInputStream;
import org.apache.commons.compress.compressors.bzip2.BZip2CompressorInputStream;
import org.apache.commons.compress.compressors.gzip.GzipCompressorInputStream;

public class TarFileExtractor {

    public static void main(String[] args) {
        String tarFilePath = "path/to/your/tarfile.tar.gz"; // Change this to your tar file path
        String outputDirectoryPath = "/tmp/unpack";

        try {
            extractTarFile(tarFilePath, outputDirectoryPath);
        } catch (IOException e) {
            System.err.println("Error extracting tar file: " + e.getMessage());
        }
    }

    public static void extractTarFile(String tarFilePath, String outputDirectoryPath) throws IOException {
        File outputFile = new File(outputDirectoryPath);
        if (!outputFile.exists()) {
            Files.createDirectories(Paths.get(outputDirectoryPath));
        }

        try (FileInputStream fileInputStream = new FileInputStream(tarFilePath);
             InputStream inputStream = createDecompressedStream(fileInputStream)) {

            TarArchiveInputStream tarInput = new TarArchiveInputStream(inputStream);

            TarArchiveEntry entry;
            while ((entry = tarInput.getNextTarEntry()) != null) {
                File outputFile = new File(outputDirectoryPath, entry.getName());

                if (entry.isDirectory()) {
                    if (!outputFile.exists() && !outputFile.mkdirs()) {
                        throw new IOException("Failed to create directory " + outputFile);
                    }
                } else {
                    File parentFile = outputFile.getParentFile();
                    if (!parentFile.exists() && !parentFile.mkdirs()) {
                        throw new IOException("Failed to create parent directories for " + outputFile);
                    }

                    try (FileOutputStream outputStream = new FileOutputStream(outputFile)) {
                        byte[] buffer = new byte[1024];
                        int bytesRead;
                        while ((bytesRead = tarInput.read(buffer)) != -1) {
                            outputStream.write(buffer, 0, bytesRead);
                        }
                    }
                }
            }
        }
    }

    private static InputStream createDecompressedStream(FileInputStream fileInputStream) throws IOException {
        try {
            if (fileInputStream.available() > 0 && fileInputStream.markSupported()) {
                fileInputStream.mark(2);
                int magic = fileInputStream.read();
                if (magic == -1) return fileInputStream;
                magic |= fileInputStream.read() << 8;

                switch (magic) {
                    case 0x1F:
                        int compressionMethod = fileInputStream.read();
                        if (compressionMethod == fileInputStream.read()) {
                            return new GzipCompressorInputStream(fileInputStream);
                        }
                        break;
                    case 0x42:
                        fileInputStream.reset();
                        return new BZip2CompressorInputStream(fileInputStream);
                }
            }
        } catch (IOException e) {
            System.err.println("Failed to detect compression type: " + e.getMessage());
        }
        return fileInputStream; // Return as is if no supported compression detected
    }
}