import java.io.*;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.zip.GZIPInputStream;

public class TarExtractor {

    public static void main(String[] args) {
        String tarFilePath = "path/to/your/archive.tar.gz";
        String destDir = "/tmp/unpack";

        try {
            extractTar(tarFilePath, destDir);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static void extractTar(String tarFilePath, String destDir) throws IOException {
        Path destinationPath = Paths.get(destDir);
        if (!Files.exists(destinationPath)) {
            Files.createDirectories(destinationPath);
        }

        try (BufferedInputStream bis = new BufferedInputStream(new FileInputStream(tarFilePath));
             InputStream inputStream = getDecompressedStream(bis, tarFilePath)) {

            TarArchiveInputStream tais = new TarArchiveInputStream(inputStream);

            TarArchiveEntry entry;
            while ((entry = tais.getNextTarEntry()) != null) {
                Path filePath = destinationPath.resolve(entry.getName());
                if (entry.isDirectory()) {
                    Files.createDirectories(filePath);
                } else {
                    Files.createDirectories(filePath.getParent());
                    try (BufferedOutputStream bos = new BufferedOutputStream(new FileOutputStream(filePath.toFile()))) {
                        byte[] buffer = new byte[1024];
                        int bytesRead;
                        while ((bytesRead = tais.read(buffer)) != -1) {
                            bos.write(buffer, 0, bytesRead);
                        }
                    }
                }
            }
        }
    }

    private static InputStream getDecompressedStream(InputStream inputStream, String filePath) throws IOException {
        if (filePath.endsWith(".gz")) {
            return new GZIPInputStream(inputStream);
        } else if (filePath.endsWith(".bz2")) {
            return new BZip2CompressorInputStream(inputStream);
        } else {
            return inputStream;
        }
    }
}
