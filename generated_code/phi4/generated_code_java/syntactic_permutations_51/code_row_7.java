import java.io.BufferedInputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.util.zip.GZIPInputStream;
import org.apache.commons.compress.archivers.tar.TarArchiveEntry;
import org.apache.commons.compress.archivers.tar.TarArchiveInputStream;

public class TarUnpacker {

    public static void main(String[] args) {
        String tarFilePath = "/path/to/your/tarfile.tar";
        String destinationDirPath = "/tmp/unpack";

        File destinationDir = new File(destinationDirPath);
        if (!destinationDir.exists()) {
            destinationDir.mkdirs();
        }

        try (BufferedInputStream bis = new BufferedInputStream(new FileInputStream(tarFilePath));
             GZIPInputStream gis = new GZIPInputStream(bis);
             TarArchiveInputStream tarIn = new TarArchiveInputStream(gis)) {

            TarArchiveEntry entry;
            while ((entry = tarIn.getNextTarEntry()) != null) {
                File outputFile = new File(destinationDir, entry.getName());
                if (entry.isDirectory()) {
                    outputFile.mkdirs();
                } else {
                    outputFile.getParentFile().mkdirs();
                    try (FileOutputStream fos = new FileOutputStream(outputFile)) {
                        byte[] buffer = new byte[1024];
                        int bytesRead;
                        while ((bytesRead = tarIn.read(buffer)) != -1) {
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
