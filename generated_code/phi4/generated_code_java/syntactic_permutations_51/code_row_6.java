import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;

import org.apache.commons.compress.archivers.tar.TarArchiveEntry;
import org.apache.commons.compress.archivers.tar.TarArchiveInputStream;
import org.apache.commons.compress.compressors.gzip.GzipCompressorInputStream;

public class TarFileExtractor {

    public static void main(String[] args) {
        String tarFilePath = "path/to/your/file.tar.gz"; // Update this path
        String destinationDirPath = "/tmp/unpack";

        File destinationDir = new File(destinationDirPath);
        if (!destinationDir.exists()) {
            boolean created = destinationDir.mkdirs();
            if (!created) {
                System.err.println("Failed to create the directory: " + destinationDirPath);
                return;
            }
        }

        try (FileOutputStream fos = new FileOutputStream(tarFilePath)) {
            // Copying file content to simulate opening a tar.gz file
            Files.copy(Paths.get(tarFilePath), fos);
        } catch (IOException e) {
            System.err.println("Error copying the file: " + e.getMessage());
            return;
        }

        try (FileInputStream fis = new FileInputStream(tarFilePath);
             GzipCompressorInputStream gzipIn = new GzipCompressorInputStream(fis);
             TarArchiveInputStream tarIn = new TarArchiveInputStream(gzipIn)) {

            TarArchiveEntry entry;
            while ((entry = tarIn.getNextTarEntry()) != null) {
                File outputFile = new File(destinationDir, entry.getName());
                if (outputFile.isDirectory() && !outputFile.exists()) {
                    boolean created = outputFile.mkdirs();
                    if (!created) {
                        System.err.println("Failed to create directory: " + outputFile.getAbsolutePath());
                    }
                } else if (entry.isFile()) {
                    try (FileOutputStream outFos = new FileOutputStream(outputFile)) {
                        byte[] buffer = new byte[1024];
                        int bytesRead;
                        while ((bytesRead = tarIn.read(buffer)) != -1) {
                            outFos.write(buffer, 0, bytesRead);
                        }
                    } catch (IOException e) {
                        System.err.println("Error writing file: " + outputFile.getAbsolutePath() + ", " + e.getMessage());
                    }
                }
            }

        } catch (IOException e) {
            System.err.println("Error processing tar file: " + e.getMessage());
        }
    }
}


Make sure to include the necessary Apache Commons Compress library in your project dependencies. You can add it via Maven:


<dependency>
    <groupId>org.apache.commons</groupId>
    <artifactId>commons-compress</artifactId>
    <version>1.21</version>
</dependency>


Or download the JAR from the [Apache Commons Compress website](https://commons.apache.org/proper/commons-compress/) and add it to your project's classpath.