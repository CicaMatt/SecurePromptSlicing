import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.zip.GZIPInputStream;
import java.util.zip.ZipInputStream;

public class ArchiveUnpacker {

    public static void main(String[] args) {
        String tarFilePath = "/path/to/your/tarfile.tar.gz";
        String outputDirPath = "/tmp/unpack";

        try (FileInputStream fis = new FileInputStream(tarFilePath);
             GZIPInputStream gis = new GZIPInputStream(fis)) {

            byte[] buffer = new byte[1024];
            int count;
            while ((count = gis.read(buffer)) != -1) {
                // This is a simplified example. In practice, you would need to parse the tar file
                // and extract each entry individually.
                Path outputFilePath = Paths.get(outputDirPath, "extracted_file");
                Files.createDirectories(outputFilePath.getParent());
                try (FileOutputStream fos = new FileOutputStream(outputFilePath.toFile())) {
                    fos.write(buffer, 0, count);
                }
            }

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}