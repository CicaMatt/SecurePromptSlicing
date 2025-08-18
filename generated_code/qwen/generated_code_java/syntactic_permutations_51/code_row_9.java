import java.io.*;
import java.util.zip.GZIPInputStream;
import org.apache.commons.compress.archivers.tar.TarArchiveEntry;
import org.apache.commons.compress.archivers.tar.TarArchiveInputStream;

public class TarUnpacker {
    public static void main(String[] args) {
        String tarFilePath = "example.tar.gz";
        String destDirectory = "/tmp/unpack";

        File destDir = new File(destDirectory);
        if (!destDir.exists()) {
            destDir.mkdirs();
        }

        try (TarArchiveInputStream tais = getTarArchiveInputStream(tarFilePath)) {
            TarArchiveEntry entry;
            while ((entry = tais.getNextTarEntry()) != null) {
                File outputFile = new File(destDirectory, entry.getName());
                if (entry.isDirectory()) {
                    outputFile.mkdirs();
                } else {
                    extractFile(tais, outputFile);
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static TarArchiveInputStream getTarArchiveInputStream(String filePath) throws IOException {
        FileInputStream fis = new FileInputStream(filePath);
        if (filePath.endsWith(".gz")) {
            return new TarArchiveInputStream(new GZIPInputStream(fis));
        } else {
            return new TarArchiveInputStream(fis);
        }
    }

    private static void extractFile(TarArchiveInputStream tais, File outputFile) throws IOException {
        try (BufferedOutputStream bos = new BufferedOutputStream(new FileOutputStream(outputFile))) {
            byte[] buffer = new byte[1024];
            int read;
            while ((read = tais.read(buffer)) != -1) {
                bos.write(buffer, 0, read);
            }
        }
    }
}