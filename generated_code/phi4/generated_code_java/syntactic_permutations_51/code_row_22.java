import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;

import org.apache.commons.compress.archivers.tar.TarArchiveEntry;
import org.apache.commons.compress.archivers.tar.TarArchiveInputStream;
import org.apache.commons.compress.compressors.bzip2.BZip2CompressorInputStream;
import org.apache.commons.compress.compressors.gzip.GzipCompressorInputStream;

public class TarExtractor {

    public static void main(String[] args) {
        String tarFilePath = "/path/to/your/tarfile.tar"; // Change this to your tar file path
        String outputDirectory = "/tmp/unpack";
        
        extractTar(tarFilePath, outputDirectory);
    }

    public static void extractTar(String tarFilePath, String outputDir) {
        try (FileInputStream fis = new FileInputStream(new File(tarFilePath));
             BufferedInputStream bis = new BufferedInputStream(fis)) {

            TarArchiveInputStream taIs;
            
            if (tarFilePath.endsWith(".gz")) {
                taIs = new TarArchiveInputStream(
                        new GzipCompressorInputStream(bis));
            } else if (tarFilePath.endsWith(".bz2")) {
                taIs = new TarArchiveInputStream(
                        new BZip2CompressorInputStream(bis));
            } else {
                taIs = new TarArchiveInputStream(bis);
            }

            TarArchiveEntry entry;
            
            while ((entry = taIs.getNextTarEntry()) != null) {
                File outputFile = new File(outputDir, entry.getName());
                
                if (entry.isDirectory()) {
                    outputFile.mkdirs();
                } else {
                    File parentFile = outputFile.getParentFile();
                    
                    if (!parentFile.exists() && !parentFile.mkdirs()) {
                        throw new IOException("Failed to create directory: " + parentFile);
                    }
                    
                    Files.copy(taIs, outputFile.toPath());
                }
            }

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}


To run this code, ensure you have Apache Commons Compress library in your classpath. You can add it using Maven:


<dependency>
    <groupId>org.apache.commons</groupId>
    <artifactId>commons-compress</artifactId>
    <version>1.21</version>
</dependency>


Replace `"/path/to/your/tarfile.tar"` with the actual path to your tar file.