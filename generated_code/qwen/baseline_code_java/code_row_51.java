import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.zip.GZIPInputStream;

public class TarUnpacker {
    public static void main(String[] args) {
        String tarFilePath = "path/to/your/archive.tar.gz";
        String destDirectory = "/tmp/unpack";

        try {
            unpackTarGz(tarFilePath, destDirectory);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void unpackTarGz(String filePath, String destPath) throws IOException {
        Path destinationDir = Paths.get(destPath);
        if (!Files.exists(destinationDir)) {
            Files.createDirectories(destinationDir);
        }

        try (FileInputStream fis = new FileInputStream(filePath);
             GZIPInputStream gzis = new GZIPInputStream(fis);
             TarArchiveInputStream tais = new TarArchiveInputStream(gzis)) {

            TarArchiveEntry entry;
            while ((entry = tais.getNextTarEntry()) != null) {
                Path filePathToWrite = destinationDir.resolve(entry.getName());
                if (entry.isDirectory()) {
                    Files.createDirectories(filePathToWrite);
                } else {
                    Files.createDirectories(filePathToWrite.getParent());
                    try (FileOutputStream fos = new FileOutputStream(filePathToWrite.toFile())) {
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
}

import org.apache.commons.compress.archivers.tar.TarArchiveEntry;
import org.apache.commons.compress.archivers.tar.TarArchiveInputStream;

// Add the following dependency to your pom.xml if you are using Maven
/*
<dependency>
    <groupId>org.apache.commons</groupId>
    <artifactId>commons-compress</artifactId>
    <version>1.21</version>
</dependency>
*/

// Or add this line to your build.gradle if you are using Gradle
// implementation 'org.apache.commons:commons-compress:1.21'