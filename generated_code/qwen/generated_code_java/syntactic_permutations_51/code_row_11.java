import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.zip.GZIPInputStream;

public class TarFileExtractor {

    public static void main(String[] args) {
        String tarFilePath = "path/to/your/file.tar.gz";
        String destDirectory = "/tmp/unpack";

        try {
            extractTarGz(tarFilePath, destDirectory);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void extractTarGz(String filePath, String destDirectory) throws IOException {
        Path destinationDir = Paths.get(destDirectory);
        if (!Files.exists(destinationDir)) {
            Files.createDirectories(destinationDir);
        }

        try (FileInputStream fis = new FileInputStream(filePath);
             GZIPInputStream gis = new GZIPInputStream(fis);
             TarArchiveInputStream tais = new TarArchiveInputStream(gis)) {

            TarArchiveEntry entry;
            while ((entry = tais.getNextTarEntry()) != null) {
                Path nextPath = destinationDir.resolve(entry.getName());
                if (entry.isDirectory()) {
                    Files.createDirectories(nextPath);
                } else {
                    Files.createDirectories(nextPath.getParent());
                    try (FileOutputStream fos = new FileOutputStream(nextPath.toFile())) {
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
