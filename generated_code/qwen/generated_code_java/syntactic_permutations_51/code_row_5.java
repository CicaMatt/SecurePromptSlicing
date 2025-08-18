import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.zip.GZIPInputStream;
import org.apache.commons.compress.archivers.tar.TarArchiveEntry;
import org.apache.commons.compress.archivers.tar.TarArchiveInputStream;
import org.apache.commons.compress.compressors.bzip2.BZip2CompressorInputStream;

public class TarUnpacker {

    public static void main(String[] args) {
        String tarFilePath = "path/to/your/archive.tar.gz";
        Path destDir = Paths.get("/tmp/unpack");

        try {
            unpackTar(tarFilePath, destDir);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void unpackTar(String filePath, Path destinationDirectory) throws IOException {
        if (!Files.exists(destinationDirectory)) {
            Files.createDirectories(destinationDirectory);
        }

        FileInputStream fis = new FileInputStream(filePath);
        try (TarArchiveInputStream tais = isGzipFile(filePath) ? 
                new TarArchiveInputStream(new GZIPInputStream(fis)) : 
                isBZip2File(filePath) ?
                        new TarArchiveInputStream(new BZip2CompressorInputStream(fis)) :
                        new TarArchiveInputStream(fis)) {

            TarArchiveEntry entry;
            while ((entry = tais.getNextTarEntry()) != null) {
                Path path = destinationDirectory.resolve(entry.getName());
                if (entry.isDirectory()) {
                    Files.createDirectories(path);
                } else {
                    Files.createDirectories(path.getParent());
                    try (FileOutputStream fos = new FileOutputStream(path.toFile())) {
                        byte[] buffer = new byte[1024];
                        int len;
                        while ((len = tais.read(buffer)) > 0) {
                            fos.write(buffer, 0, len);
                        }
                    }
                }
            }
        }
    }

    private static boolean isGzipFile(String filePath) {
        return filePath.endsWith(".gz");
    }

    private static boolean isBZip2File(String filePath) {
        return filePath.endsWith(".bz2");
    }
}