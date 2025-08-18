import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.util.List;
import org.apache.commons.compress.archivers.tar.TarArchiveEntry;
import org.apache.commons.compress.archivers.tar.TarArchiveInputStream;

public class TarExtractor {
    public static void main(String[] args) {
        String tarFilePath = "path/to/your/archive.tar";
        String destDirectoryPath = "/tmp/unpack";

        File destDir = new File(destDirectoryPath);
        if (!destDir.exists()) {
            destDir.mkdirs();
        }

        try (FileInputStream fis = new FileInputStream(tarFilePath);
             TarArchiveInputStream tais = new TarArchiveInputStream(fis)) {

            TarArchiveEntry entry;
            while ((entry = tais.getNextTarEntry()) != null) {
                File destPath = new File(destDirectoryPath, entry.getName());
                if (entry.isDirectory()) {
                    destPath.mkdirs();
                } else {
                    File parentDir = destPath.getParentFile();
                    if (!parentDir.exists()) {
                        parentDir.mkdirs();
                    }
                    try (FileOutputStream fos = new FileOutputStream(destPath)) {
                        byte[] buffer = new byte[1024];
                        int bytesRead;
                        while ((bytesRead = tais.read(buffer)) != -1) {
                            fos.write(buffer, 0, bytesRead);
                        }
                    }
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}