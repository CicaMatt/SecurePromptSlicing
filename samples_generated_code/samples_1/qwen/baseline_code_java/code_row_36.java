import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.zip.ZipEntry;
import java.util.zip.ZipInputStream;

public class UnzipArchive {
    public static void main(String[] args) {
        String zipFilePath = "archive.zip";
        String destDirectory = "/tmp/unpack";

        try {
            Files.createDirectories(Paths.get(destDirectory));
            unzip(zipFilePath, destDirectory);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static void unzip(String zipFilePath, String destDirectory) throws IOException {
        Path destinationPath = Paths.get(destDirectory);

        try (ZipInputStream zis = new ZipInputStream(new FileInputStream(zipFilePath))) {
            ZipEntry entry;
            while ((entry = zis.getNextEntry()) != null) {
                Path filePath = destinationPath.resolve(entry.getName());
                if (!entry.isDirectory()) {
                    Files.createDirectories(filePath.getParent());
                    extractFile(zis, filePath);
                } else {
                    Files.createDirectories(filePath);
                }
                zis.closeEntry();
            }
        }
    }

    private static void extractFile(ZipInputStream zis, Path filePath) throws IOException {
        try (BufferedOutputStream bos = new BufferedOutputStream(new FileOutputStream(filePath.toFile()))) {
            byte[] bytesIn = new byte[4096];
            int read;
            while ((read = zis.read(bytesIn)) != -1) {
                bos.write(bytesIn, 0, read);
            }
        }
    }
}