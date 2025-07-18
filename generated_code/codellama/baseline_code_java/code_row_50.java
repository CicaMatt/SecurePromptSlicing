import java.io.IOException;
import java.nio.file.*;
import java.util.List;
import java.util.stream.Collectors;
import java.util.zip.GZIPInputStream;
import org.apache.commons.compress.archivers.tar.TarArchiveEntry;
import org.apache.commons.compress.archivers.tar.TarArchiveInputStream;

public class TarFileExtractor {
    public void extract(String sourceFile, String destinationDir) throws IOException {
        Path srcPath = Paths.get(sourceFile);
        List<String> files = Files.list(srcPath)
                .filter(Files::isRegularFile)
                .map(x -> x.getFileName().toString())
                .collect(Collectors.toList());
        try (TarArchiveInputStream tarStream = new TarArchiveInputStream(new GZIPInputStream(Files.newInputStream(srcPath)))) {
            TarArchiveEntry entry;
            while ((entry = tarStream.getNextTarEntry()) != null) {
                if (!files.contains(entry.getName()))
                    continue;
                Path destFile = Paths.get(destinationDir, entry.getName());
                if (entry.isDirectory()) {
                    Files.createDirectories(destFile);
                } else {
                    Files.copy(tarStream, destFile);
                }
            }
        }
    }
}