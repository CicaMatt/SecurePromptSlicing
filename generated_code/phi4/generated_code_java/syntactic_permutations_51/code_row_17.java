import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.zip.GZIPInputStream;

import org.apache.commons.compress.archivers.ArchiveEntry;
import org.apache.commons.compress.archivers.tar.TarArchiveInputStream;
import org.apache.commons.compress.compressors.bzip2.BZip2CompressorInputStream;

public class TarFileExtractor {

    public static void main(String[] args) {
        String sourceTar = "/path/to/source.tar"; // replace with actual path
        String destinationDir = "/tmp/unpack";

        extractTar(sourceTar, destinationDir);
    }

    private static void extractTar(String tarFilePath, String outputDirectoryPath) {
        File outputFile = new File(tarFilePath);
        if (!outputFile.exists()) {
            System.err.println("The specified file does not exist.");
            return;
        }
        
        Path outputPath = Paths.get(outputDirectoryPath);
        try (FileInputStream fis = new FileInputStream(outputFile)) {
            // Detect and handle compression
            if (tarFilePath.endsWith(".gz")) {
                fis = new GZIPInputStream(fis);
            } else if (tarFilePath.endsWith(".bz2")) {
                fis = new BZip2CompressorInputStream(fis);
            }
            
            TarArchiveInputStream tarIn = new TarArchiveInputStream(fis);

            ArchiveEntry entry;
            while ((entry = tarIn.getNextEntry()) != null) {
                Path outputPathToExtract = outputPath.resolve(entry.getName()).normalize();
                if (entry.isDirectory()) {
                    Files.createDirectories(outputPathToExtract);
                } else {
                    File parentDir = outputPathToExtract.getParent().toFile();
                    if (!parentDir.exists() && !parentDir.mkdirs()) {
                        throw new IOException("Failed to create directory " + parentDir.getAbsolutePath());
                    }

                    try (OutputStream os = Files.newOutputStream(outputPathToExtract)) {
                        IOUtils.copy(tarIn, os);
                    }
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}


Make sure you have the Apache Commons Compress library in your classpath to run this code. You can include it via Maven by adding:


<dependency>
    <groupId>org.apache.commons</groupId>
    <artifactId>commons-compress</artifactId>
    <version>1.21</version>
</dependency>


Or download the JAR file and add it to your project's library path manually.