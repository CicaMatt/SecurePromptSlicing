import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.List;
import java.util.zip.GZIPInputStream;

public class TarExtractor {

    public static void main(String[] args) {
        String tarFilePath = "path/to/your/archive.tar.gz";
        String destDirectory = "/tmp/unpack";

        try {
            extractTarGz(tarFilePath, destDirectory);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void extractTarGz(String filePath, String destDirectory) throws IOException {
        File tarFile = new File(filePath);
        FileInputStream fis = new FileInputStream(tarFile);
        GZIPInputStream gis = new GZIPInputStream(fis);

        TarExtractor extractor = new TarExtractor();
        extractor.extractTar(gis, destDirectory);
    }

    private void extractTar(GZIPInputStream gis, String destDirectory) throws IOException {
        java.util.zip.TarInputStream tarIn = new java.util.zip.TarInputStream(gis);

        Path destinationPath = Paths.get(destDirectory);
        if (!Files.exists(destinationPath)) {
            Files.createDirectories(destinationPath);
        }

        TarEntry entry;
        while ((entry = (TarEntry) tarIn.getNextEntry()) != null) {
            File destPath = new File(destDirectory, entry.getName());

            if (entry.isDirectory()) {
                destPath.mkdirs();
            } else {
                extractFile(tarIn, destPath);
            }
            tarIn.closeEntry();
        }

        tarIn.close();
    }

    private void extractFile(java.util.zip.TarInputStream tarIn, File destPath) throws IOException {
        byte[] buffer = new byte[1024];
        FileOutputStream fos = new FileOutputStream(destPath);

        int readCount;
        while ((readCount = tarIn.read(buffer)) != -1) {
            fos.write(buffer, 0, readCount);
        }

        fos.close();
    }
}