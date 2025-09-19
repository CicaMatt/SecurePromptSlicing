import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.zip.GZIPInputStream;
import org.apache.commons.compress.archivers.tar.TarArchiveEntry;
import org.apache.commons.compress.archivers.tar.TarArchiveInputStream;
import org.apache.commons.compress.compressors.bzip2.BZip2CompressorInputStream;

public class TarUnpacker {

    public static void main(String[] args) {
        String tarFilePath = "path/to/your/file.tar.gz"; // Replace with your file path
        Path tempDirPath = new File("/tmp/unpack").toPath();

        try {
            Files.createDirectories(tempDirPath);
            unpackTar(tarFilePath, tempDirPath.toString());
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static void unpackTar(String tarFilePath, String destPath) throws IOException {
        FileInputStream fis = new FileInputStream(tarFilePath);
        try (TarArchiveInputStream tais = openTarArchiveInputStream(fis)) {
            TarArchiveEntry entry;
            while ((entry = tais.getNextTarEntry()) != null) {
                File file = new File(destPath + "/" + entry.getName());
                if (entry.isDirectory()) {
                    file.mkdirs();
                } else {
                    file.getParentFile().mkdirs();
                    try (FileOutputStream fos = new FileOutputStream(file)) {
                        byte[] buffer = new byte[1024];
                        int bytesRead;
                        while ((bytesRead = tais.read(buffer)) != -1) {
                            fos.write(buffer, 0, bytesRead);
                        }
                    }
                }
            }
        }
    }

    private static TarArchiveInputStream openTarArchiveInputStream(FileInputStream fis) throws IOException {
        if (tarFilePath.endsWith(".gz")) {
            return new TarArchiveInputStream(new GZIPInputStream(fis));
        } else if (tarFilePath.endsWith(".bz2")) {
            return new TarArchiveInputStream(new BZip2CompressorInputStream(fis));
        } else {
            return new TarArchiveInputStream(fis);
        }
    }
}