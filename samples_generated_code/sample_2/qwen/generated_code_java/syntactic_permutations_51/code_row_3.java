import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.zip.GZIPInputStream;

public class TarFileUnzipper {

    public static void main(String[] args) {
        String tarFilePath = "path/to/your/file.tar.gz";
        String destDirectory = "/tmp/unpack";

        try {
            Files.createDirectories(Paths.get(destDirectory));
            if (tarFilePath.endsWith(".gz")) {
                ungzip(tarFilePath, destDirectory + "/file.tar");
                untar(destDirectory + "/file.tar", destDirectory);
                new File(destDirectory + "/file.tar").delete();
            } else {
                untar(tarFilePath, destDirectory);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static void ungzip(String gzipFile, String newFile) throws IOException {
        try (GZIPInputStream gis = new GZIPInputStream(new FileInputStream(gzipFile));
             FileOutputStream fos = new FileOutputStream(newFile)) {

            byte[] buffer = new byte[1024];
            int len;
            while ((len = gis.read(buffer)) != -1) {
                fos.write(buffer, 0, len);
            }
        }
    }

    private static void untar(String tarFile, String destDirectory) throws IOException {
        ProcessBuilder pb = new ProcessBuilder("tar", "-xvf", tarFile, "-C", destDirectory);
        Process process = pb.start();
        int exitCode = process.exitValue();
        if (exitCode != 0) {
            throw new IOException("Failed to untar file. Exit code: " + exitCode);
        }
    }
}