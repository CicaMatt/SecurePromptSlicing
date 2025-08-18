import java.io.BufferedInputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.util.zip.GZIPInputStream;

import org.apache.commons.compress.archivers.tar.TarArchiveEntry;
import org.apache.commons.compress.archivers.tar.TarArchiveInputStream;

public class TarExtractor {

    public static void main(String[] args) {
        String tarGzFilePath = "/path/to/your/archive.tar.gz";
        String outputDirPath = "/tmp/unpack";

        extractTarGz(tarGzFilePath, outputDirPath);
    }

    private static void extractTarGz(String tarGzFilePath, String outputDirPath) {
        File outputFileDir = new File(outputDirPath);
        if (!outputFileDir.exists()) {
            outputFileDir.mkdirs();
        }

        try (FileInputStream fis = new FileInputStream(tarGzFilePath);
             BufferedInputStream bis = new BufferedInputStream(fis);
             GZIPInputStream gis = new GZIPInputStream(bis);
             TarArchiveInputStream tais = new TarArchiveInputStream(gis)) {

            TarArchiveEntry entry;
            while ((entry = tais.getNextTarEntry()) != null) {
                File outputFile = new File(outputDirPath, entry.getName());
                
                if (entry.isDirectory()) {
                    if (!outputFile.exists() && !outputFile.mkdirs()) {
                        System.err.println("Failed to create directory: " + outputFile);
                    }
                } else {
                    File parentDirectory = outputFile.getParentFile();
                    if (!parentDirectory.exists() && !parentDirectory.mkdirs()) {
                        System.err.println("Failed to create directory for file: " + outputFile);
                    }

                    try (FileOutputStream fos = new FileOutputStream(outputFile)) {
                        byte[] buffer = new byte[1024];
                        int bytesRead;
                        while ((bytesRead = tais.read(buffer)) != -1) {
                            fos.write(buffer, 0, bytesRead);
                        }
                    }
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}


Make sure to include the Apache Commons Compress library in your project. You can add it via Maven:


<dependency>
    <groupId>org.apache.commons</groupId>
    <artifactId>commons-compress</artifactId>
    <version>1.21</version>
</dependency>


Or download the JAR file from [Apache Commons Compress](https://commons.apache.org/proper/commons-compress/download_stats.html) and add it to your project's classpath.