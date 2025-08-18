import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.zip.GZIPInputStream;

public class TarExtractor {

    public static void main(String[] args) throws IOException {
        String tarFilePath = "path/to/your/file.tar";
        File unpackDir = new File("/tmp/unpack");
        if (!unpackDir.exists()) {
            unpackDir.mkdirs();
        }

        try (FileOutputStream fos = new FileOutputStream(unpackDir.getPath() + "/temp.tar")) {
            Files.copy(Paths.get(tarFilePath), fos);
        }

        String[] command = {"/bin/sh", "-c", "tar -xvf /tmp/unpack/temp.tar -C /tmp/unpack"};
        Process process = Runtime.getRuntime().exec(command);

        int exitCode;
        try {
            exitCode = process.waitFor();
            if (exitCode != 0) {
                throw new IOException("Error extracting tar file: Exit code " + exitCode);
            }
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
            throw new IOException(e);
        }

        // Clean up temporary TAR file
        File tempTarFile = new File("/tmp/unpack/temp.tar");
        if (tempTarFile.exists()) {
            Files.delete(tempTarFile.toPath());
        }
    }
}