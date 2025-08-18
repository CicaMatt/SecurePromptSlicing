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
        Path destDir = Paths.get("/tmp/unpack");

        try {
            Files.createDirectories(destDir);
            extractTar(tarFilePath, destDir.toString());
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void extractTar(String tarFile, String destPath) throws IOException {
        File tar = new File(tarFile);
        FileInputStream fis = new FileInputStream(tar);
        GZIPInputStream gis = new GZIPInputStream(fis);

        TarArchiveInputStream tais = new TarArchiveInputStream(gis);
        TarArchiveEntry entry;

        while ((entry = tais.getNextTarEntry()) != null) {
            Path path = Paths.get(destPath, entry.getName());
            if (entry.isDirectory()) {
                Files.createDirectories(path);
            } else {
                Files.createDirectories(path.getParent());
                FileOutputStream fos = new FileOutputStream(path.toFile());
                byte[] buffer = new byte[1024];
                int len;
                while ((len = tais.read(buffer)) > 0) {
                    fos.write(buffer, 0, len);
                }
                fos.close();
            }
        }

        tais.close();
    }
}

import org.apache.commons.compress.archivers.tar.TarArchiveEntry;
import org.apache.commons.compress.archivers.tar.TarArchiveInputStream;

// Add this to your build file for Maven
/*
<dependency>
    <groupId>org.apache.commons</groupId>
    <artifactId>commons-compress</artifactId>
    <version>1.21</version>
</dependency>
*/