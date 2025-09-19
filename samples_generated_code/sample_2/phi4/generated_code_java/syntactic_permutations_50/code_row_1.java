import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.Enumeration;

import org.apache.commons.compress.archivers.tar.TarArchiveEntry;
import org.apache.commons.compress.archivers.tar.TarArchiveInputStream;
import org.apache.commons.compress.compressors.z.ZCodecFactory;
import org.apache.commons.compress.compressors.z.UncompressorInputStream;
import org.apache.commons.compress.utils.IOUtils;

public class ZipToTarExtractor {

    public static void main(String[] args) throws IOException {
        String zipFilePath = "archive.zip";
        File zipFile = new File(zipFilePath);

        try (FileInputStream fis = new FileInputStream(zipFile);
             UncompressorInputStream uncompressorInputStream = ZCodecFactory.createZUncompressor().getStream(fis, null)) {

            TarArchiveInputStream tarInput = new TarArchiveInputStream(uncompressorInputStream);
            TarArchiveEntry entry;
            
            while ((entry = (TarArchiveEntry) tarInput.getNextEntry()) != null) {
                File outputFile = new File(entry.getName());
                
                if (!entry.isDirectory()) {
                    Files.createDirectories(outputFile.toPath().getParent());
                    try (FileOutputStream fos = new FileOutputStream(outputFile)) {
                        IOUtils.copy(tarInput, fos);
                    }
                }
            }
        }
    }
}


To run this code, ensure you have the necessary dependencies in your project. If using Maven, add these to your `pom.xml`:


<dependencies>
    <dependency>
        <groupId>org.apache.commons</groupId>
        <artifactId>commons-compress</artifactId>
        <version>1.21</version>
    </dependency>
</dependencies>


Replace `"archive.zip"` with the path to your ZIP file containing a TAR archive.