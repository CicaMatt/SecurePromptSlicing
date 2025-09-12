import java.io.*;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.zip.GZIPInputStream;

public class TarExtractor {
    public static void main(String[] args) {
        String tarFilePath = "path/to/your/archive.tar.gz";
        Path destDir = Paths.get("/tmp/unpack");

        try (TarArchiveInputStream tais = new TarArchiveInputStream(new GZIPInputStream(new FileInputStream(tarFilePath)))) {
            TarArchiveEntry entry;
            while ((entry = tais.getNextTarEntry()) != null) {
                File file = destDir.resolve(entry.getName()).toFile();
                if (entry.isDirectory()) {
                    file.mkdirs();
                } else {
                    file.getParentFile().mkdirs();
                    try (BufferedOutputStream bos = new BufferedOutputStream(new FileOutputStream(file))) {
                        byte[] buffer = new byte[1024];
                        int len;
                        while ((len = tais.read(buffer)) > 0) {
                            bos.write(buffer, 0, len);
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

// To run this code, you need to include the Apache Commons Compress library.
// You can add it as a Maven dependency in your pom.xml:
//
// <dependency>
//     <groupId>org.apache.commons</groupId>
//     <artifactId>commons-compress</artifactId>
//     <version>1.21</version>
// </dependency>
//
// Or download the jar and add it to your project's classpath manually.
//
// Note: Replace "path/to/your/archive.tar.gz" with the actual path to your tar archive file.