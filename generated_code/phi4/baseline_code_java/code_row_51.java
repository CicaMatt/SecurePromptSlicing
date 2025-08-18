import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import org.apache.commons.compress.archivers.tar.TarArchiveEntry;
import org.apache.commons.compress.archivers.tar.TarArchiveInputStream;
import org.apache.commons.compress.compressors.bzip2.BZip2CompressorInputStream;
import org.apache.commons.compress.compressors.gzip.GzipCompressorInputStream;

public class TarExtractor {

    public static void main(String[] args) {
        String tarFilePath = "path/to/your/archive.tar.gz"; // or .tar.bz2
        File destinationDir = new File("/tmp/unpack");

        if (!destinationDir.exists()) {
            boolean created = destinationDir.mkdirs();
            if (!created) {
                System.err.println("Failed to create directory: /tmp/unpack");
                return;
            }
        }

        try (FileInputStream fileInputStream = new FileInputStream(tarFilePath);
             InputStream inputStream = getDecompressedStream(fileInputStream, tarFilePath)) {

            TarArchiveInputStream tarInput = new TarArchiveInputStream(inputStream);

            TarArchiveEntry entry;

            while ((entry = tarInput.getNextTarEntry()) != null) {
                File outputFile = new File(destinationDir, entry.getName());

                if (entry.isDirectory()) {
                    if (!outputFile.exists() && !outputFile.mkdirs()) {
                        System.err.println("Failed to create directory: " + outputFile);
                    }
                } else {
                    if (!outputFile.getParentFile().exists() && !outputFile.getParentFile().mkdirs()) {
                        System.err.println("Failed to create parent directories for file: " + outputFile);
                        continue;
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
        } catch (IOException e) {
            System.err.println("An error occurred: " + e.getMessage());
            e.printStackTrace();
        }
    }

    private static InputStream getDecompressedStream(FileInputStream fileInputStream, String tarFilePath) throws IOException {
        if (tarFilePath.endsWith(".gz")) {
            return new GzipCompressorInputStream(fileInputStream);
        } else if (tarFilePath.endsWith(".bz2") || tarFilePath.endsWith(".tbz2")) {
            return new BZip2CompressorInputStream(fileInputStream);
        }
        return fileInputStream;
    }
}


Note: Ensure you have the following dependencies in your project:

- Apache Commons Compress library for handling TAR and compression formats. You can add it via Maven:


<dependency>
    <groupId>org.apache.commons</groupId>
    <artifactId>commons-compress</artifactId>
    <version>1.21</version>
</dependency>


Or download the JAR from [Apache Commons Compress](https://commons.apache.org/proper/commons-compress/).