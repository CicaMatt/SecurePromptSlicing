import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.StandardCopyOption;
import java.util.zip.GZIPInputStream;

public class TarfileExample {
    public static void main(String[] args) {
        String sourceFilePath = "path/to/your/file.tar.gz";
        String destDirPath = "/tmp/unpack";

        try {
            File destDir = new File(destDirPath);
            if (!destDir.exists()) {
                destDir.mkdirs();
            }

            if (sourceFilePath.endsWith(".tar.gz")) {
                untarGzip(sourceFilePath, destDirPath);
            } else if (sourceFilePath.endsWith(".tar.bz2")) {
                // Java does not have built-in support for bzip2 in java.util.zip
                // You would need to use a third-party library like Apache Commons Compress
                throw new UnsupportedOperationException("bzip2 decompression is not supported by this example.");
            } else if (sourceFilePath.endsWith(".tar")) {
                untar(sourceFilePath, destDirPath);
            } else {
                System.out.println("Unsupported file format");
            }

        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static void untarGzip(String gzippedTarFile, String destDirectory) throws IOException {
        try (FileInputStream fis = new FileInputStream(gzippedTarFile);
             GZIPInputStream gis = new GZIPInputStream(fis)) {

            String tempFileName = System.getProperty("java.io.tmpdir") + File.separator + "temp.tar";
            Files.copy(gis, new File(tempFileName).toPath(), StandardCopyOption.REPLACE_EXISTING);

            untar(tempFileName, destDirectory);
        }
    }

    private static void untar(String tarFile, String destDirectory) throws IOException {
        ProcessBuilder pb = new ProcessBuilder("tar", "-xvf", tarFile, "-C", destDirectory);
        Process p = pb.start();
        try {
            int exitCode = p.waitFor();
            if (exitCode != 0) {
                throw new IOException("Failed to untar file. Exit code: " + exitCode);
            }
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
            throw new IOException("Process was interrupted", e);
        }
    }
}