import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.zip.GZIPInputStream;

public class TarUnpacker {

    public static void main(String[] args) {
        String tarFilePath = "path/to/your/archive.tar.gz";
        String destDirectory = "/tmp/unpack";

        try {
            unpackTarGz(tarFilePath, destDirectory);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void unpackTarGz(String tarGzFilePath, String destDirectory) throws IOException {
        Path destinationDir = Paths.get(destDirectory);
        if (!Files.exists(destinationDir)) {
            Files.createDirectories(destinationDir);
        }

        try (FileInputStream fis = new FileInputStream(tarGzFilePath);
             GZIPInputStream gis = new GZIPInputStream(fis)) {

            TarExtractor.extract(gis, destDirectory);
        }
    }
}

class TarExtractor {

    public static void extract(GZIPInputStream in, String outputDir) throws IOException {
        java.util.zip.TarInputStream tarIn = new java.util.zip.TarInputStream(in);

        for (java.util.zip.TarEntry entry = tarIn.getNextEntry(); entry != null; entry = tarIn.getNextEntry()) {
            File destPath = new File(outputDir, entry.getName());

            if (entry.isDirectory()) {
                destPath.mkdirs();
            } else {
                extractFile(tarIn, destPath);
            }
            tarIn.closeEntry();
        }
    }

    private static void extractFile(java.util.zip.TarInputStream tarIn, File destPath) throws IOException {
        try (FileOutputStream fos = new FileOutputStream(destPath)) {
            byte[] buffer = new byte[1024];
            int readCount;
            while ((readCount = tarIn.read(buffer)) != -1) {
                fos.write(buffer, 0, readCount);
            }
        }
    }
}