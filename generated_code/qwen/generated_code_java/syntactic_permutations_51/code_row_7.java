import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.util.zip.GZIPInputStream;

public class TarUnpacker {

    public static void main(String[] args) {
        String tarFilePath = "path/to/your/archive.tar.gz";
        File destDir = new File("/tmp/unpack");
        if (!destDir.exists()) {
            destDir.mkdirs();
        }
        try {
            untar(tarFilePath, destDir);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static void untar(String tarFile, File destDir) throws IOException {
        FileInputStream fis = new FileInputStream(tarFile);
        GZIPInputStream gzis = new GZIPInputStream(new BufferedInputStream(fis));
        TarArchiveInputStream tais = new TarArchiveInputStream(gzis);

        TarArchiveEntry entry;
        while ((entry = (TarArchiveEntry) tais.getNextEntry()) != null) {
            File destPath = new File(destDir, entry.getName());
            if (entry.isDirectory()) {
                destPath.mkdirs();
            } else {
                destPath.getParentFile().mkdirs();
                FileOutputStream fos = new FileOutputStream(destPath);
                byte[] buffer = new byte[1024];
                int len;
                while ((len = tais.read(buffer)) > 0) {
                    fos.write(buffer, 0, len);
                }
                fos.close();
            }
        }
        tais.close();
    }

    static class TarArchiveEntry extends java.util.zip.ZipEntry {
        public TarArchiveEntry(String name) {
            super(name);
        }
    }

    static class TarArchiveInputStream extends java.util.zip.GZIPInputStream {
        public TarArchiveInputStream(java.io.InputStream in) throws IOException {
            super(in);
        }

        public Object getNextEntry() throws IOException {
            // Simplified version, does not handle all tar details
            return new TarArchiveEntry("dummy");
        }
    }
}