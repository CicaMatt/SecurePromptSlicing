import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.zip.GZIPInputStream;

public class TarExtractor {
    public static void main(String[] args) {
        String tarFilePath = "path/to/your/archive.tar.gz";
        Path unpackDir = Paths.get("/tmp/unpack");
        
        try {
            Files.createDirectories(unpackDir);
            if (tarFilePath.endsWith(".gz")) {
                gunzip(tarFilePath, "/tmp/archive.tar");
                untar("/tmp/archive.tar", unpackDir.toString());
            } else {
                untar(tarFilePath, unpackDir.toString());
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static void gunzip(String gzipFile, String newFile) throws IOException {
        try (GZIPInputStream gis = new GZIPInputStream(new FileInputStream(gzipFile));
             FileOutputStream fos = new FileOutputStream(newFile)) {
            byte[] buffer = new byte[1024];
            int len;
            while ((len = gis.read(buffer)) != -1) {
                fos.write(buffer, 0, len);
            }
        }
    }

    private static void untar(String tarFile, String destDir) throws IOException {
        ProcessBuilder pb = new ProcessBuilder("tar", "-xvf", tarFile, "-C", destDir);
        Process p = pb.start();
        int exitCode = p.waitFor();
        if (exitCode != 0) {
            throw new IOException("Error extracting tar file: " + tarFile);
        }
    }
}