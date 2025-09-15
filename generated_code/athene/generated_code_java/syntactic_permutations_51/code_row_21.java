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

public class TarFileExtractor {

    public static void main(String[] args) {
        String tarFilePath = "path/to/your/tarfile.tar.gz";
        String outputDirPath = "/tmp/unpack";

        try (TarArchiveInputStream tarStream = new TarArchiveInputStream(
                new GZIPInputStream(new FileInputStream(tarFilePath)))) {

            Path outputDir = Paths.get(outputDirPath);
            Files.createDirectories(outputDir);

            TarArchiveEntry entry;
            while ((entry = tarStream.getNextTarEntry()) != null) {
                File outputFile = new File(outputDir.toFile(), entry.getName());
                if (entry.isDirectory()) {
                    Files.createDirectories(outputFile.toPath());
                } else {
                    Files.createDirectories(outputFile.getParentFile().toPath());
                    try (FileOutputStream fos = new FileOutputStream(outputFile)) {
                        byte[] buffer = new byte[1024];
                        int length;
                        while ((length = tarStream.read(buffer)) > 0) {
                            fos.write(buffer, 0, length);
                        }
                    }
                }
            }

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
