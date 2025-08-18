import java.io.*;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.zip.GZIPInputStream;

public class TarExtractor {

    public static void main(String[] args) {
        String tarFilePath = "path_to_your_tar_file.tar.gz";
        String destDir = "/tmp/unpack";

        try {
            extractTar(tarFilePath, destDir);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static void extractTar(String tarPath, String destDir) throws IOException {
        Path destinationPath = Paths.get(destDir);
        if (!Files.exists(destinationPath)) {
            Files.createDirectories(destinationPath);
        }

        try (InputStream fis = new FileInputStream(tarPath);
             InputStream is = tarPath.endsWith(".gz") ? new GZIPInputStream(fis) : fis;
             TarArchiveInputStream tais = new TarArchiveInputStream(is)) {

            TarArchiveEntry entry;
            while ((entry = tais.getNextTarEntry()) != null) {
                Path path = destinationPath.resolve(entry.getName());
                if (entry.isDirectory()) {
                    Files.createDirectories(path);
                    continue;
                }
                try (BufferedOutputStream bos = new BufferedOutputStream(new FileOutputStream(path.toFile()))) {
                    byte[] buffer = new byte[1024];
                    int read;
                    while ((read = tais.read(buffer)) != -1) {
                        bos.write(buffer, 0, read);
                    }
                }
            }
        }
    }
}

import org.apache.commons.compress.archivers.tar.TarArchiveEntry;
import org.apache.commons.compress.archivers.tar.TarArchiveInputStream;

// Add this dependency to your pom.xml if you are using Maven
/*
<dependency>
    <groupId>org.apache.commons</groupId>
    <artifactId>commons-compress</artifactId>
    <version>1.21</version>
</dependency>
*/