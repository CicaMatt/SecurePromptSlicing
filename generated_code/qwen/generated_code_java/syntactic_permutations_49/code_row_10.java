import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.zip.ZipEntry;
import java.util.zip.ZipInputStream;

public class UnzipExample {
    public static void main(String[] args) {
        String zipFilePath = "path/to/your/file.zip"; // Replace with your zip file path
        String destDirectory = "/tmp/unpack";
        try {
            unzip(zipFilePath, destDirectory);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void unzip(String zipFilePath, String destDirectory) throws IOException {
        Path destinationPath = Paths.get(destDirectory);
        if (!Files.exists(destinationPath)) {
            Files.createDirectories(destinationPath);
        }

        try (ZipInputStream zis = new ZipInputStream(new FileInputStream(zipFilePath))) {
            ZipEntry entry;
            while ((entry = zis.getNextEntry()) != null) {
                String filePath = destDirectory + File.separator + entry.getName();
                if (!entry.isDirectory()) {
                    extractFile(zis, filePath);
                } else {
                    Files.createDirectories(Paths.get(filePath));
                }
                zis.closeEntry();
            }
        }
    }

    private static void extractFile(ZipInputStream zipIn, String filePath) throws IOException {
        try (BufferedOutputStream bos = new BufferedOutputStream(new FileOutputStream(filePath))) {
            byte[] bytesIn = new byte[4096];
            int read;
            while ((read = zipIn.read(bytesIn)) != -1) {
                bos.write(bytesIn, 0, read);
            }
        }
    }
}