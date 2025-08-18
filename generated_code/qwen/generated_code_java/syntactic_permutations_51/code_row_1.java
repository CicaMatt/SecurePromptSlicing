import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.zip.GZIPInputStream;

public class TarFileExtractor {

    public static void main(String[] args) {
        String tarFilePath = "path/to/your/file.tar.gz";
        File destDir = new File("/tmp/unpack");

        if (!destDir.exists()) {
            destDir.mkdirs();
        }

        try (FileInputStream fis = new FileInputStream(tarFilePath);
             GZIPInputStream gzis = new GZIPInputStream(fis)) {

            tarUnarchive(gzis, destDir);

        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static void tarUnarchive(GZIPInputStream gzis, File destDir) throws IOException {
        ProcessBuilder pb = new ProcessBuilder("tar", "-xzf", "-", "-C", destDir.getAbsolutePath());
        pb.redirectErrorStream(true);

        try (Process process = pb.start();
             FileOutputStream fos = new FileOutputStream(process.getOutputStream())) {

            byte[] buffer = new byte[1024];
            int length;
            while ((length = gzis.read(buffer)) >= 0) {
                fos.write(buffer, 0, length);
            }

            fos.flush();

            int exitCode = process.waitFor();
            if (exitCode != 0) {
                throw new IOException("Tar extraction failed with exit code " + exitCode);
            }
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
            throw new IOException("Process was interrupted", e);
        }
    }
}