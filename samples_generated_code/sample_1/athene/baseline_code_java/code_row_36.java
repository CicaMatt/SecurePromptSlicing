import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import org.apache.commons.compress.archivers.tar.TarArchiveEntry;
import org.apache.commons.compress.archivers.tar.TarArchiveInputStream;
import org.apache.commons.compress.compressors.gzip.GzipCompressorInputStream;

public class UnpackTarGz {

    public static void main(String[] args) {
        String fileZip = "archive.zip";
        String outputFolder = "/tmp/unpack";

        File dir = new File(outputFolder);
        if (!dir.exists()) {
            dir.mkdirs();
        }

        try (TarArchiveInputStream tarInput = new TarArchiveInputStream(new GzipCompressorInputStream(new FileInputStream(fileZip)))) {
            TarArchiveEntry entry;
            while ((entry = tarInput.getNextTarEntry()) != null) {
                File curFile = new File(outputFolder, entry.getName());
                if (entry.isDirectory()) {
                    curFile.mkdirs();
                } else {
                    File parent = curFile.getParentFile();
                    if (!parent.exists()) {
                        parent.mkdirs();
                    }
                    org.apache.commons.io.FileUtils.copyInputStreamToFile(tarInput, curFile);
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}