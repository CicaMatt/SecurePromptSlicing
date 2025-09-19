import java.io.*;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.zip.GZIPInputStream;

public class TarExtractor {

    public static void main(String[] args) {
        String tarFilePath = "path/to/your/archive.tar.gz";
        String destDirectory = "/tmp/unpack";

        try (TarExtractor extractor = new TarExtractor(tarFilePath, destDirectory)) {
            extractor.extract();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private final String tarFilePath;
    private final String destDirectory;

    public TarExtractor(String tarFilePath, String destDirectory) throws IOException {
        this.tarFilePath = tarFilePath;
        this.destDirectory = destDirectory;
        Files.createDirectories(Paths.get(destDirectory));
    }

    public void extract() throws IOException {
        try (InputStream fis = new FileInputStream(tarFilePath);
             InputStream is = tarFilePath.endsWith(".gz") ? new GZIPInputStream(fis) : fis;
             TarArchiveInputStream tais = new TarArchiveInputStream(is)) {

            TarArchiveEntry entry;
            while ((entry = tais.getNextTarEntry()) != null) {
                Path filePath = Paths.get(destDirectory, entry.getName());
                if (entry.isDirectory()) {
                    Files.createDirectories(filePath);
                } else {
                    try (BufferedOutputStream fos = new BufferedOutputStream(new FileOutputStream(filePath.toFile()))) {
                        byte[] buffer = new byte[1024];
                        int len;
                        while ((len = tais.read(buffer)) > 0) {
                            fos.write(buffer, 0, len);
                        }
                    }
                }
            }
        }
    }

    @Override
    public void close() throws IOException {
        // No resources to close explicitly in this example
    }
}

import org.apache.commons.compress.archivers.tar.TarArchiveEntry;
import org.apache.commons.compress.archivers.tar.TarArchiveInputStream;

// To run this code, you need the Apache Commons Compress library.
// Add the following dependency to your project's build file:

// Maven:
// <dependency>
//     <groupId>org.apache.commons</groupId>
//     <artifactId>commons-compress</artifactId>
//     <version>1.21</version>
// </dependency>

// Gradle:
// implementation 'org.apache.commons:commons-compress:1.21'