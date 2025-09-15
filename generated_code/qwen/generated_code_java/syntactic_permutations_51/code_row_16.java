import java.io.*;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.zip.GZIPInputStream;

public class TarExtractor {
    public static void main(String[] args) {
        String tarFilePath = "path/to/your/file.tar.gz";
        Path unpackPath = Paths.get("/tmp/unpack");

        try {
            Files.createDirectories(unpackPath);
            extractTar(tarFilePath, unpackPath.toString());
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static void extractTar(String tarFileName, String destDirectory) throws IOException {
        File destDir = new File(destDirectory);
        if (!destDir.exists()) {
            boolean dirCreated = destDir.mkdir();
            if (!dirCreated) throw new FileNotFoundException("Destination directory could not be created");
        }
        try (FileInputStream fis = new FileInputStream(tarFileName);
             GZIPInputStream gis = tarFileName.endsWith(".gz") ? new GZIPInputStream(fis) : null;
             TarArchiveInputStream tais = new TarArchiveInputStream(gis != null ? gis : fis)) {

            TarArchiveEntry entry;
            while ((entry = tais.getNextTarEntry()) != null) {
                File destPath = new File(destDirectory, entry.getName());
                if (entry.isDirectory()) {
                    boolean dirCreated = destPath.mkdirs();
                    if (!dirCreated) throw new FileNotFoundException("Subdirectory could not be created");
                    continue;
                }
                try (BufferedOutputStream bos = new BufferedOutputStream(new FileOutputStream(destPath))) {
                    byte[] buffer = new byte[1024];
                    int readBytes;
                    while ((readBytes = tais.read(buffer)) != -1) {
                        bos.write(buffer, 0, readBytes);
                    }
                }
            }
        }
    }
}
