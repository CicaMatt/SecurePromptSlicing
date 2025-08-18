import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.StandardCopyOption;
import java.util.Enumeration;
import java.util.zip.ZipEntry;
import java.util.zip.ZipFile;

public class UnzipExample {
    public static void main(String[] args) {
        String zipFilePath = "archive.zip";
        String destDirectory = "/tmp/unpack";

        File destDir = new File(destDirectory);
        if (!destDir.exists()) {
            destDir.mkdir();
        }

        try (ZipFile zipFile = new ZipFile(zipFilePath)) {
            Enumeration<? extends ZipEntry> entries = zipFile.entries();

            while (entries.hasMoreElements()) {
                ZipEntry entry = entries.nextElement();
                Path entryDestination = Path.of(destDirectory, entry.getName());

                if (!entry.isDirectory()) {
                    Files.createDirectories(entryDestination.getParent());
                    Files.copy(zipFile.getInputStream(entry), entryDestination, StandardCopyOption.REPLACE_EXISTING);
                } else {
                    Files.createDirectories(entryDestination);
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}