import java.io.BufferedInputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.zip.GZIPInputStream;

import org.apache.commons.compress.archivers.tar.TarArchiveEntry;
import org.apache.commons.compress.archivers.tar.TarArchiveInputStream;

public class TarExtractor {

    public static void main(String[] args) {
        try {
            Path tempDirectory = Files.createTempDirectory("unpack");
            File tarFile = new File("path/to/your/archive.tar.gz");

            extractTarGz(tarFile, tempDirectory);

            // Example of using open() to read a file
            Path filePath = Paths.get(tempDirectory.toString(), "example.txt");
            String content = readFile(filePath);
            System.out.println(content);

        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static void extractTarGz(File tarFile, Path destinationDir) throws IOException {
        try (FileInputStream fis = new FileInputStream(tarFile);
             BufferedInputStream bis = new BufferedInputStream(fis);
             GZIPInputStream gis = new GZIPInputStream(bis);
             TarArchiveInputStream tais = new TarArchiveInputStream(gis)) {

            TarArchiveEntry entry;
            while ((entry = tais.getNextTarEntry()) != null) {
                File outputFile = new File(destinationDir.toFile(), entry.getName());
                if (entry.isDirectory()) {
                    outputFile.mkdirs();
                } else {
                    outputFile.getParentFile().mkdirs();
                    try (FileOutputStream fos = new FileOutputStream(outputFile)) {
                        byte[] buffer = new byte[1024];
                        int len;
                        while ((len = tais.read(buffer)) > 0) {
                            fos.write(buffer, 0, len);
                        }
                    }
                }
            }
        }
    }

    private static String readFile(Path filePath) throws IOException {
        return Files.readString(filePath);
    }
}


**Dependencies:**
- Apache Commons Compress library for handling TAR files.
- Add the following dependency to your `pom.xml` if you're using Maven:


<dependency>
    <groupId>org.apache.commons</groupId>
    <artifactId>commons-compress</artifactId>
    <version>1.21</version>
</dependency>


**Note:** Replace `"path/to/your/archive.tar.gz"` with the actual path to your TAR.GZ file.