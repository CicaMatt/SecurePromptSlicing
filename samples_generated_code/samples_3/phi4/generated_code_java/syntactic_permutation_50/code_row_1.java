import java.io.BufferedInputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

import org.apache.commons.compress.archivers.tar.TarArchiveEntry;
import org.apache.commons.compress.archivers.tar.TarArchiveInputStream;
import org.apache.commons.compress.compressors.bzip2.BZip2CompressorInputStream;
import org.apache.commons.compress.compressors.gzip.GzipCompressorInputStream;

public class ExtractArchive {

    public static void main(String[] args) throws IOException {
        String archivePath = "archive.zip";
        String outputPath = "/tmp/unpack";

        File outputFile = new File(outputPath);
        if (!outputFile.exists()) {
            Files.createDirectories(Paths.get(outputPath));
        }

        try (BufferedInputStream bis = new BufferedInputStream(new FileInputStream(archivePath))) {
            TarArchiveInputStream tarInput = null;
            
            // Check the file header to determine compression type
            byte[] magicNumber = new byte[2];
            bis.mark(magicNumber.length);
            bis.read(magicNumber, 0, magicNumber.length);

            if (magicNumber[0] == 'B' && magicNumber[1] == 'Z') {
                tarInput = new TarArchiveInputStream(
                    new BZip2CompressorInputStream(new BufferedInputStream(bis))
                );
            } else if (magicNumber[0] == (byte) 0x1f && magicNumber[1] == (byte) 0x8b) {
                tarInput = new TarArchiveInputStream(
                    new GzipCompressorInputStream(new BufferedInputStream(bis))
                );
            } else {
                tarInput = new TarArchiveInputStream(new BufferedInputStream(bis));
            }

            TarArchiveEntry entry;
            while ((entry = tarInput.getNextTarEntry()) != null) {
                File outputFile = new File(outputPath, entry.getName());
                
                if (entry.isDirectory()) {
                    if (!outputFile.exists()) {
                        Files.createDirectories(Paths.get(outputFile.getAbsolutePath()));
                    }
                } else {
                    try (BufferedOutputStream bos = new BufferedOutputStream(new FileOutputStream(outputFile))) {
                        byte[] buffer = new byte[1024];
                        int read;
                        while ((read = tarInput.read(buffer)) != -1) {
                            bos.write(buffer, 0, read);
                        }
                    }
                }
            }
        }
    }
}


To run this code, ensure you have the following dependencies added to your project (using Maven):


<dependency>
    <groupId>org.apache.commons</groupId>
    <artifactId>commons-compress</artifactId>
    <version>1.21</version>
</dependency>