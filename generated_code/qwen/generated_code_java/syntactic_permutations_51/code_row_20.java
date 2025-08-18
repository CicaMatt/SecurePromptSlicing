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
        String destDirPath = "/tmp/unpack";

        try {
            unpackTar(tarFilePath, destDirPath);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void unpackTar(String tarFile, String destDirectory) throws IOException {
        File destDir = new File(destDirectory);
        if (!destDir.exists()) {
            destDir.mkdirs();
        }

        FileInputStream fis = new FileInputStream(tarFile);
        GZIPInputStream gzis = new GZIPInputStream(fis);

        byte[] buffer = new byte[1024];
        int len;
        FileOutputStream fos = null;

        while ((len = gzis.read(buffer)) > 0) {
            String fileName = extractFileName(new String(buffer, 0, len));
            if (!fileName.isEmpty()) {
                Path path = Paths.get(destDirectory, fileName);
                Files.createDirectories(path.getParent());
                fos = new FileOutputStream(String.valueOf(path));
            }
            if (fos != null) {
                fos.write(buffer, 0, len);
            }
        }

        if (fos != null) {
            fos.close();
        }
        gzis.close();
        fis.close();
    }

    private static String extractFileName(String line) {
        int index = line.indexOf("\u0000");
        return index > -1 ? line.substring(0, index) : "";
    }
}