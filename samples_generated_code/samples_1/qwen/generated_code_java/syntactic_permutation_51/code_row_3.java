import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.zip.GZIPInputStream;

public class TarUnpacker {

    public static void main(String[] args) {
        String tarFilePath = "example.tar.gz";
        String destDirectory = "/tmp/unpack";

        try {
            unpackTarGz(tarFilePath, destDirectory);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void unpackTarGz(String tarGzPath, String destDirectory) throws IOException {
        Path destinationDir = Files.createDirectories(new File(destDirectory).toPath());
        try (FileInputStream fis = new FileInputStream(tarGzPath);
             GZIPInputStream gis = new GZIPInputStream(fis)) {
            untar(gis, destinationDir);
        }
    }

    private static void untar(GZIPInputStream gis, Path destDirectory) throws IOException {
        java.util.tar.TarArchiveInputStream tais = new java.util.tar.TarArchiveInputStream(gis);
        TarArchiveEntry entry;

        while ((entry = tais.getNextTarEntry()) != null) {
            File destPath = destinationDir.resolve(entry.getName()).toFile();
            if (entry.isDirectory()) {
                Files.createDirectories(destPath.toPath());
            } else {
                Files.createDirectories(destPath.getParentFile().toPath());
                try (FileOutputStream fos = new FileOutputStream(destPath)) {
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