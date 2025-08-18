import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.zip.GZIPInputStream;
import java.util.zip.ZipEntry;
import java.util.zip.ZipInputStream;

public class ArchiveExtractor {

    public static void main(String[] args) {
        String tarFilePath = "example.tar.gz";
        String destinationDir = "/tmp/unpack";

        try (FileInputStream fis = new FileInputStream(tarFilePath);
             GZIPInputStream gis = new GZIPInputStream(fis)) {

            byte[] buffer = new byte[1024];
            int length;
            File destDir = new File(destinationDir);
            if (!destDir.exists()) {
                destDir.mkdir();
            }

            Path tempTarFile = Files.createTempFile("temp", ".tar");
            try (FileOutputStream fos = new FileOutputStream(tempTarFile.toFile())) {
                while ((length = gis.read(buffer)) > 0) {
                    fos.write(buffer, 0, length);
                }
            }

            try (TarArchiveInputStream tais = new TarArchiveInputStream(new FileInputStream(tempTarFile.toFile()))) {
                TarArchiveEntry entry;
                while ((entry = tais.getNextTarEntry()) != null) {
                    File destPath = new File(destinationDir, entry.getName());
                    if (entry.isDirectory()) {
                        destPath.mkdirs();
                    } else {
                        Files.copy(tais, destPath.toPath());
                    }
                }
            }

            Files.delete(tempTarFile);

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}

Note: This code requires the Apache Commons Compress library for handling tar files. Add the following dependency to your project's build file:


<dependency>
    <groupId>org.apache.commons</groupId>
    <artifactId>commons-compress</artifactId>
    <version>1.21</version>
</dependency>