import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

import org.apache.commons.compress.archivers.tar.TarArchiveEntry;
import org.apache.commons.compress.archivers.tar.TarArchiveInputStream;
import org.apache.commons.compress.compressors.gzip.GzipCompressorInputStream;
import org.apache.commons.compress.compressors.bzip2.BZip2CompressorInputStream;

public class TarUnpacker {

    private static final String EXTRACT_PATH = "/tmp/unpack";

    public static void main(String[] args) {
        Path tarFilePath = Paths.get("path/to/your/tarfile.tar.gz"); // Update with your tar file path
        unpackTarFile(tarFilePath);
    }

    public static void unpackTarFile(Path tarFilePath) {
        try (BufferedReader reader = new BufferedReader(new FileReader(tarFilePath.toFile()))) {
            byte[] buffer = new byte[1024];
            Path extractPath = Paths.get(EXTRACT_PATH);
            Files.createDirectories(extractPath);

            if (tarFilePath.toString().endsWith(".gz")) {
                try (GzipCompressorInputStream gzipIn =
                        new GzipCompressorInputStream(reader)) {

                    unpack(gzipIn, buffer, extractPath);
                }
            } else if (tarFilePath.toString().endsWith(".bz2")) {
                try (BZip2CompressorInputStream bzip2In =
                        new BZip2CompressorInputStream(reader)) {

                    unpack(bzip2In, buffer, extractPath);
                }
            } else {
                File tarFile = tarFilePath.toFile();
                try (TarArchiveInputStream tarIn = new TarArchiveInputStream(new FileReader(tarFile))) {

                    unpack(tarIn, buffer, extractPath);
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static void unpack(org.apache.commons.compress.archivers.tar.TarArchiveInputStream tarIn,
                               byte[] buffer, Path extractPath)
            throws IOException {

        TarArchiveEntry entry;
        while ((entry = tarIn.getNextTarEntry()) != null) {
            if (entry.isDirectory()) {
                Files.createDirectories(extractPath.resolve(entry.getName()));
                continue;
            }

            Path filePath = extractPath.resolve(entry.getName());
            File parent = filePath.toFile().getParentFile();
            if (parent != null) {
                parent.mkdirs();
            }
            try (BufferedOutputStream out = new BufferedOutputStream(new FileOutputStream(filePath.toFile()))) {
                int count;
                while ((count = tarIn.read(buffer)) != -1) {
                    out.write(buffer, 0, count);
                }
            }
        }
    }
}


**Dependencies:**

You need to include the following dependencies in your `pom.xml` if you are using Maven:


<dependency>
    <groupId>org.apache.commons</groupId>
    <artifactId>commons-compress</artifactId>
    <version>1.21</version>
</dependency>


For Gradle, add this to your `build.gradle` file:


implementation 'org.apache.commons:commons-compress:1.21'