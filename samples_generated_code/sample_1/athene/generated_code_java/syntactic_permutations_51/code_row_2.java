import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.zip.GZIPInputStream;
import java.util.zip.ZipInputStream;

public class TarFileUnzipper {

    public static void main(String[] args) {
        try (TarArchiveInputStream tarInput = new TarArchiveInputStream(new GZIPInputStream(
                new FileInputStream("path/to/your/tar.gz")))) {
            File outputDir = new File("/tmp/unpack");
            if (!outputDir.exists()) {
                Files.createDirectories(outputDir.toPath());
            }
            TarArchiveEntry entry;
            while ((entry = tarInput.getNextTarEntry()) != null) {
                Path entryPath = Paths.get(outputDir.getAbsolutePath(), entry.getName());
                if (entry.isDirectory()) {
                    Files.createDirectory(entryPath);
                } else {
                    try (FileOutputStream fos = new FileOutputStream(entryPath.toFile())) {
                        byte[] buffer = new byte[1024];
                        int length;
                        while ((length = tarInput.read(buffer)) > 0) {
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