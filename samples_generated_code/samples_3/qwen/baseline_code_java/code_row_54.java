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
        File tarFile = new File(tarFilePath);
        Path destinationPath = Paths.get(destDir);

        if (!Files.exists(destinationPath)) {
            Files.createDirectories(destinationPath);
        }

        try (InputStream is = new FileInputStream(tarFile);
             InputStream gis = tarFile.getName().endsWith(".gz") ? new GZIPInputStream(is) : is;
             TarArchiveInputStream tais = new TarArchiveInputStream(gis)) {

            TarArchiveEntry entry;
            while ((entry = tais.getNextTarEntry()) != null) {
                Path newPath = destinationPath.resolve(entry.getName());
                if (entry.isDirectory()) {
                    Files.createDirectories(newPath);
                } else {
                    try (OutputStream os = Files.newOutputStream(newPath)) {
                        byte[] buffer = new byte[4096];
                        int len;
                        while ((len = tais.read(buffer, 0, buffer.length)) != -1) {
                            os.write(buffer, 0, len);
                        }
                    }
                }
            }
        }
    }
}
