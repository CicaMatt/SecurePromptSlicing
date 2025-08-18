import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.util.Enumeration;

import org.apache.commons.compress.archivers.tar.TarArchiveEntry;
import org.apache.commons.compress.archivers.tar.TarArchiveInputStream;
import org.apache.commons.compress.compressors.z.ZipCompressorInputStream;

public class UnzipTarArchive {

    public static void main(String[] args) throws IOException {
        File zipFile = new File("archive.zip");
        if (!zipFile.exists()) {
            System.err.println("The file archive.zip does not exist.");
            return;
        }

        // Create output directory
        File outputDir = new File(".");
        if (!outputDir.exists() && !outputDir.mkdirs()) {
            System.err.println("Failed to create output directory.");
            return;
        }

        try (FileInputStream fis = new FileInputStream(zipFile);
             ZipCompressorInputStream zis = new ZipCompressorInputStream(fis);
             TarArchiveInputStream tarInput = new TarArchiveInputStream(zis)) {

            TarArchiveEntry entry;
            while ((entry = tarInput.getNextTarEntry()) != null) {
                File outputFile = new File(outputDir, entry.getName());
                if (entry.isDirectory()) {
                    outputFile.mkdirs();
                } else {
                    // Ensure parent directories are created
                    File parentFile = outputFile.getParentFile();
                    if (!parentFile.exists() && !parentFile.mkdirs()) {
                        throw new IOException("Failed to create directory: " + parentFile);
                    }
                    try (FileOutputStream fos = new FileOutputStream(outputFile)) {
                        byte[] buffer = new byte[1024];
                        int len;
                        while ((len = tarInput.read(buffer)) != -1) {
                            fos.write(buffer, 0, len);
                        }
                    }
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}


Note: This code requires the Apache Commons Compress library. You can add it to your project via Maven by including:


<dependency>
    <groupId>org.apache.commons</groupId>
    <artifactId>commons-compress</artifactId>
    <version>1.21</version>
</dependency>


Or download the jar from [Apache Commons Compress](https://commons.apache.org/proper/commons-compress/) and add it to your project's classpath manually.