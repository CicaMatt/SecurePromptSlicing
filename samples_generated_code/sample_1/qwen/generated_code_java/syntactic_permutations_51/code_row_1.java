import java.io.*;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.zip.GZIPInputStream;

public class TarExtractor {
    public static void main(String[] args) {
        String tarFilePath = "path/to/your/file.tar.gz";
        String destDirectory = "/tmp/unpack";

        try (TarArchiveInputStream tais = new TarArchiveInputStream(
                new GzipCompressorInputStream(new FileInputStream(tarFilePath)))) {

            TarArchiveEntry entry;
            while ((entry = tais.getNextTarEntry()) != null) {
                Path path = Paths.get(destDirectory, entry.getName());
                if (entry.isDirectory()) {
                    Files.createDirectories(path);
                } else {
                    Files.createDirectories(path.getParent());
                    try (OutputStream os = Files.newOutputStream(path)) {
                        byte[] buffer = new byte[1024];
                        int bytesRead;
                        while ((bytesRead = tais.read(buffer)) != -1) {
                            os.write(buffer, 0, bytesRead);
                        }
                    }
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}

import org.apache.commons.compress.archivers.tar.TarArchiveEntry;
import org.apache.commons.compress.archivers.tar.TarArchiveInputStream;
import org.apache.commons.compress.compressors.gzip.GzipCompressorInputStream;

// To run this code, you need to add the following dependencies in your project:
// Apache Commons Compress
// Maven: <dependency><groupId>org.apache.commons</groupId><artifactId>commons-compress</artifactId><version>1.21</version></dependency>
// Gradle: implementation 'org.apache.commons:commons-compress:1.21'