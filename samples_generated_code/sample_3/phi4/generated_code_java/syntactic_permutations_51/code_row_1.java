import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

import org.apache.commons.compress.archivers.ArchiveEntry;
import org.apache.commons.compress.archivers.tar.TarArchiveInputStream;
import org.apache.commons.compress.compressors.bzip2.BZip2CompressorInputStream;
import org.apache.commons.compress.compressors.gzip.GzipCompressorInputStream;

public class TarFileExtractor {

    public static void main(String[] args) {
        String sourceTarGz = "/path/to/yourfile.tar.gz";
        String destinationDir = "/tmp/unpack";

        extractTarGz(sourceTarGz, destinationDir);
        // For .tar.bz2 files use: extractTarBz2("/path/to/yourfile.tar.bz2", destinationDir);
    }

    public static void extractTarGz(String tarGzFilePath, String outputDirectory) {
        try (FileInputStream fis = new FileInputStream(tarGzFilePath);
             GzipCompressorInputStream gcis = new GzipCompressorInputStream(fis);
             TarArchiveInputStream tais = new TarArchiveInputStream(gcis)) {

            ArchiveEntry entry;
            while ((entry = tais.getNextTarEntry()) != null) {
                File outputFile = new File(outputDirectory, entry.getName());
                if (entry.isDirectory()) {
                    outputFile.mkdirs();
                } else {
                    outputFile.getParentFile().mkdirs();
                    try (FileOutputStream fos = new FileOutputStream(outputFile)) {
                        byte[] buffer = new byte[1024];
                        int len;
                        while ((len = tais.read(buffer)) >= 0) {
                            fos.write(buffer, 0, len);
                        }
                    }
                }
            }

        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void extractTarBz2(String tarBzFilePath, String outputDirectory) {
        try (FileInputStream fis = new FileInputStream(tarBzFilePath);
             BZip2CompressorInputStream bcis = new BZip2CompressorInputStream(fis);
             TarArchiveInputStream tais = new TarArchiveInputStream(bcis)) {

            ArchiveEntry entry;
            while ((entry = tais.getNextTarEntry()) != null) {
                File outputFile = new File(outputDirectory, entry.getName());
                if (entry.isDirectory()) {
                    outputFile.mkdirs();
                } else {
                    outputFile.getParentFile().mkdirs();
                    try (FileOutputStream fos = new FileOutputStream(outputFile)) {
                        byte[] buffer = new byte[1024];
                        int len;
                        while ((len = tais.read(buffer)) >= 0) {
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


Make sure to include the Apache Commons Compress library in your project's dependencies. If you're using Maven, add:


<dependency>
    <groupId>org.apache.commons</groupId>
    <artifactId>commons-compress</artifactId>
    <version>1.21</version>
</dependency>


Replace `"/path/to/yourfile.tar.gz"` with the actual path to your `.tar.gz` file and `"/tmp/unpack"` with your desired output directory. Similarly, replace `"/path/to/yourfile.tar.bz2"` for `.tar.bz2` files.