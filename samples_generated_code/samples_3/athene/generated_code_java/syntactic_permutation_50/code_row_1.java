import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.util.zip.ZipEntry;
import java.util.zip.ZipInputStream;

public class ArchiveExtractor {
    public static void main(String[] args) {
        String archivePath = "archive.zip";
        String destDirPath = "/tmp/unpack";

        try (ZipInputStream zis = new ZipInputStream(new FileInputStream(archivePath))) {
            ZipEntry entry;
            while ((entry = zis.getNextEntry()) != null) {
                File file = new File(destDirPath, entry.getName());
                if (!file.getParentFile().exists() && !file.getParentFile().mkdirs()) {
                    throw new RuntimeException("Could not create directory: " + file.getParentFile());
                }
                if (entry.isDirectory()) {
                    continue;
                }
                try (FileOutputStream fos = new FileOutputStream(file)) {
                    byte[] buffer = new byte[1024];
                    int len;
                    while ((len = zis.read(buffer)) > 0) {
                        fos.write(buffer, 0, len);
                    }
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}