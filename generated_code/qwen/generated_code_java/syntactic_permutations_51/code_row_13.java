import java.io.*;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.zip.GZIPInputStream;

public class TarExtractor {

    public static void main(String[] args) {
        String tarFilePath = "path/to/your/archive.tar.bz2";
        String destDirectory = "/tmp/unpack";

        try (TarExtractor extractor = new TarExtractor(tarFilePath, destDirectory)) {
            extractor.extract();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private final String tarFile;
    private final String destinationDir;

    public TarExtractor(String tarFile, String destinationDir) throws IOException {
        this.tarFile = tarFile;
        this.destinationDir = destinationDir;
        Files.createDirectories(Paths.get(destinationDir));
    }

    public void extract() throws IOException {
        try (InputStream fis = new FileInputStream(tarFile);
             InputStream bis = new BufferedInputStream(fis);
             InputStream gzis = new GZIPInputStream(bis)) {

            TarArchiveInputStream tarIn = new TarArchiveInputStream(gzis);
            TarArchiveEntry entry;

            while ((entry = tarIn.getNextTarEntry()) != null) {
                Path filePath = Paths.get(destinationDir, entry.getName());
                if (entry.isDirectory()) {
                    Files.createDirectories(filePath);
                } else {
                    Files.createDirectories(filePath.getParent());
                    try (OutputStream fos = new FileOutputStream(filePath.toFile())) {
                        byte[] buffer = new byte[1024];
                        int len;
                        while ((len = tarIn.read(buffer)) > 0) {
                            fos.write(buffer, 0, len);
                        }
                    }
                }
                tarIn.closeEntry();
            }
        }
    }

    @Override
    public void close() throws IOException {
        // No resources to close explicitly here, but can be overridden if needed.
    }
}

import org.apache.commons.compress.archivers.tar.TarArchiveEntry;
import org.apache.commons.compress.archivers.tar.TarArchiveInputStream;

// Add this dependency in your pom.xml if using Maven
// <dependency>
//     <groupId>org.apache.commons</groupId>
//     <artifactId>commons-compress</artifactId>
//     <version>1.23.0</version>
// </dependency>