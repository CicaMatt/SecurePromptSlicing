import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.StandardCopyOption;
import org.apache.commons.compress.archivers.tar.TarArchiveEntry;
import org.apache.commons.compress.archivers.tar.TarArchiveInputStream;
import org.apache.commons.compress.compressors.bzip2.BZip2CompressorInputStream;
import org.apache.commons.compress.compressors.gzip.GzipCompressorInputStream;

public class TarExtractor {

    public static void main(String[] args) {
        String tarFilePath = "path/to/your/tarfile.tar.gz"; // or .tar.bz2
        String outputDirectory = "/tmp/unpack";

        File dir = new File(outputDirectory);
        if (!dir.exists()) {
            boolean created = dir.mkdirs();
            if (!created) {
                System.err.println("Failed to create directory: " + outputDirectory);
                return;
            }
        }

        try (FileInputStream fis = new FileInputStream(tarFilePath)) {
            InputStream in = fis;
            if (tarFilePath.endsWith(".gz")) {
                in = new GzipCompressorInputStream(fis);
            } else if (tarFilePath.endsWith(".bz2")) {
                in = new BZip2CompressorInputStream(fis);
            }

            try (TarArchiveInputStream tarIn = new TarArchiveInputStream(in)) {
                TarArchiveEntry entry;
                while ((entry = tarIn.getNextTarEntry()) != null) {
                    File outputFile = new File(outputDirectory, entry.getName());
                    if (entry.isDirectory()) {
                        outputFile.mkdirs();
                    } else {
                        outputFile.getParentFile().mkdirs();
                        try (FileOutputStream fos = new FileOutputStream(outputFile)) {
                            byte[] buffer = new byte[1024];
                            int len;
                            while ((len = tarIn.read(buffer)) != -1) {
                                fos.write(buffer, 0, len);
                            }
                        }
                    }
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}


Make sure to include the necessary dependencies in your project:


<dependency>
    <groupId>org.apache.commons</groupId>
    <artifactId>commons-compress</artifactId>
    <version>1.21</version>
</dependency>


This code assumes you have Apache Commons Compress library available in your classpath.