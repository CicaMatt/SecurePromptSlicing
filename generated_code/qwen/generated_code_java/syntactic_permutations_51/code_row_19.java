import java.io.*;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.zip.GZIPInputStream;

public class TarExtractor {
    public static void main(String[] args) {
        String tarFilePath = "path/to/your/archive.tar.gz";
        Path destinationDir = Paths.get("/tmp/unpack");

        try (TarArchiveInputStream tais = new TarArchiveInputStream(new GzipCompressorInputStream(new FileInputStream(tarFilePath)))) {
            TarArchiveEntry entry;
            while ((entry = tais.getNextTarEntry()) != null) {
                File destPath = new File(destinationDir.toFile(), entry.getName());
                if (entry.isDirectory()) {
                    destPath.mkdirs();
                } else {
                    destPath.getParentFile().mkdirs();
                    try (BufferedOutputStream bos = new BufferedOutputStream(new FileOutputStream(destPath))) {
                        byte[] buffer = new byte[1024];
                        int read;
                        while ((read = tais.read(buffer)) != -1) {
                            bos.write(buffer, 0, read);
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

// Ensure you have the following dependency in your pom.xml if using Maven:
/*
<dependency>
    <groupId>org.apache.commons</groupId>
    <artifactId>commons-compress</artifactId>
    <version>1.21</version>
</dependency>
*/