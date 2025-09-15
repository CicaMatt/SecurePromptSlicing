import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.StandardCopyOption;

import org.apache.commons.compress.archivers.tar.TarArchiveEntry;
import org.apache.commons.compress.archivers.tar.TarArchiveInputStream;
import org.apache.commons.compress.compressors.zip.ZipCompressorInputStream;

public class UnzipZipToTar {

    public static void main(String[] args) {
        File archive = new File("archive.zip");
        File extractDir = new File("/tmp/unpack");

        if (!extractDir.exists()) {
            extractDir.mkdirs();
        }

        try (FileInputStream fis = new FileInputStream(archive);
             ZipCompressorInputStream zis = new ZipCompressorInputStream(fis)) {

            TarArchiveInputStream tarInput = new TarArchiveInputStream(zis);

            TarArchiveEntry entry;
            while ((entry = tarInput.getNextTarEntry()) != null) {
                File outputFile = new File(extractDir, entry.getName());
                if (entry.isDirectory()) {
                    outputFile.mkdirs();
                } else {
                    outputFile.getParentFile().mkdirs();
                    try (FileOutputStream fos = new FileOutputStream(outputFile)) {
                        byte[] buffer = new byte[1024];
                        int len;
                        while ((len = tarInput.read(buffer)) != -1) {
                            fos.write(buffer, 0, len);
                        }
                    }
                }
            }

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
