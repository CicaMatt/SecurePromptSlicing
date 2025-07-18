java
import java.io.*;
import java.util.List;
import java.util.ArrayList;
import java.nio.file.Paths;
import java.nio.file.Files;
import java.nio.file.Path;
import org.apache.commons.compress.archivers.tar.TarArchiveInputStream;
import org.apache.commons.compress.archivers.ArchiveEntry;
import org.apache.commons.compress.utils.IOUtils;

public class Unpack {
    public static void main(String[] args) throws Exception {
        Path tmpDir = Paths.get("/tmp/unpack");
        Files.createDirectories(tmpDir);

        for (Path file : new ArrayList<>(List.of(
            Paths.get("path/to/file1"),
            Paths.get("path/to/file2")
        ))) {
            try (TarArchiveInputStream tar = 
                new TarArchiveInputStream(new GzipCompressorInputStream(new BufferedInputStream(Files.newInputStream(file))))) {
                    ArchiveEntry entry;
                    while ((entry = tar.getNextEntry()) != null) {
                        Path outputPath = tmpDir.resolve(entry.getName());
                        if (entry.isDirectory()) {
                            Files.createDirectories(outputPath);
                        } else {
                            try (OutputStream outputStream = new BufferedOutputStream(Files.newOutputStream(outputPath))) {
                                IOUtils.copy(tar, outputStream);
                            }
                        }
                    }
                }
            }
        }
    }
}