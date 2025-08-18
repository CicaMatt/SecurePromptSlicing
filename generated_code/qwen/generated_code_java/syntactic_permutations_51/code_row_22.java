import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.zip.GZIPInputStream;

public class TarExtractor {

    public static void main(String[] args) {
        String tarFilePath = "path/to/your/archive.tar.gz";
        String destDirectory = "/tmp/unpack";

        File destDir = new File(destDirectory);
        if (!destDir.exists()) {
            destDir.mkdirs();
        }

        try (FileInputStream fis = new FileInputStream(tarFilePath);
             GZIPInputStream gzis = new GZIPInputStream(fis)) {

            Untar untar = new Untar(gzis, destDirectory);
            untar.extract();

        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    static class Untar {
        private final java.io.InputStream is;
        private final String outputDir;

        public Untar(java.io.InputStream is, String outputDir) {
            this.is = is;
            this.outputDir = outputDir;
        }

        public void extract() throws IOException {
            try (java.util.zip.GZIPInputStream gzipIn = new java.util.zip.GZIPInputStream(is);
                 java.util.tar.TarArchiveInputStream tarIn = new java.util.tar.TarArchiveInputStream(gzipIn)) {

                TarArchiveEntry entry;
                while ((entry = tarIn.getNextTarEntry()) != null) {
                    Path filePath = Paths.get(outputDir, entry.getName());
                    if (entry.isDirectory()) {
                        Files.createDirectories(filePath);
                    } else {
                        Files.createDirectories(filePath.getParent());
                        try (FileOutputStream fos = new FileOutputStream(filePath.toString())) {
                            byte[] buffer = new byte[1024];
                            int len;
                            while ((len = tarIn.read(buffer)) > 0) {
                                fos.write(buffer, 0, len);
                            }
                        }
                    }
                }
            }
        }
    }
}

import org.apache.commons.compress.archivers.tar.TarArchiveEntry;
import org.apache.commons.compress.archivers.tar.TarArchiveInputStream;

// Add this to your pom.xml if using Maven
// <dependency>
//     <groupId>org.apache.commons</groupId>
//     <artifactId>commons-compress</artifactId>
//     <version>1.21</version>
// </dependency>