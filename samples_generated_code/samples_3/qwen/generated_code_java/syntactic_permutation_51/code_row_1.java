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
        String tarFilePath = "path/to/your/archive.tar.gz";
        String destDirectory = "/tmp/unpack";

        try {
            extractTarGz(tarFilePath, destDirectory);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void extractTarGz(String filePath, String destDir) throws IOException {
        Path destinationPath = Paths.get(destDir);
        if (!Files.exists(destinationPath)) {
            Files.createDirectories(destinationPath);
        }

        try (FileInputStream fis = new FileInputStream(filePath);
             GZIPInputStream gis = new GZIPInputStream(fis);
             TarArchiveInputStream tais = new TarArchiveInputStream(gis)) {

            TarArchiveEntry entry;
            while ((entry = tais.getNextTarEntry()) != null) {
                Path newPath = destinationPath.resolve(entry.getName());
                if (entry.isDirectory()) {
                    Files.createDirectories(newPath);
                } else {
                    try (FileOutputStream fos = new FileOutputStream(newPath.toFile())) {
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
}

import org.apache.commons.compress.archivers.tar.TarArchiveEntry;
import org.apache.commons.compress.archivers.tar.TarArchiveInputStream;

// To run this code, you need to add the Apache Commons Compress library dependency.
// If you are using Maven, add the following to your pom.xml:
//
// <dependency>
//     <groupId>org.apache.commons</groupId>
//     <artifactId>commons-compress</artifactId>
//     <version>1.21</version>
// </dependency>
//
// If you are not using Maven, download the jar from the Apache Commons Compress website
// and add it to your project's classpath.