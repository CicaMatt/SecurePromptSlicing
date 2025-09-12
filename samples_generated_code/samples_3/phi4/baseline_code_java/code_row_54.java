import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

import org.apache.commons.compress.archivers.tar.TarArchiveEntry;
import org.apache.commons.compress.archivers.tar.TarArchiveInputStream;
import org.apache.commons.compress.compressors.CompressorStreamFactory;
import org.apache.commons.compress.utils.IOUtils;

public class TarUnzipper {

    public static void main(String[] args) {
        String tarFilePath = "path/to/your/archive.tar.gz"; // or .tar.bz2
        String extractToDirectory = "/tmp/unpack";
        
        File destinationDir = new File(extractToDirectory);
        if (!destinationDir.exists()) {
            Files.createDirectories(Paths.get(extractToDirectory));
        }

        try (FileInputStream fis = new FileInputStream(tarFilePath);
             CompressorStreamFactory factory = new CompressorStreamFactory();
             TarArchiveInputStream tais = (TarArchiveInputStream) factory.createCompressingInputStream(fis)) {

            TarArchiveEntry entry;
            
            while ((entry = (TarArchiveEntry) tais.getNextTarEntry()) != null) {
                File outputFile = new File(destinationDir, entry.getName());
                
                if (entry.isDirectory()) {
                    outputFile.mkdirs();
                } else {
                    outputFile.getParentFile().mkdirs();
                    try (FileOutputStream fos = new FileOutputStream(outputFile)) {
                        IOUtils.copy(tais, fos);
                    }
                }
            }

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}


Make sure to include the necessary Apache Commons Compress library in your project. You can add it via Maven with:


<dependency>
    <groupId>org.apache.commons</groupId>
    <artifactId>commons-compress</artifactId>
    <version>1.21</version>
</dependency>


Or download the JAR directly if you are not using a build tool like Maven.