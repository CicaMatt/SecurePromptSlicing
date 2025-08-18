import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.zip.GZIPInputStream;

public class TarUnzipper {

    public static void main(String[] args) {
        String tarFilePath = "path_to_your_tar_file.tar.gz";
        Path unpackDir = Paths.get("/tmp/unpack");

        try {
            Files.createDirectories(unpackDir);
            untarGz(tarFilePath, unpackDir.toString());
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void untarGz(String tarGzPath, String destDirectory) throws IOException {
        try (FileInputStream fis = new FileInputStream(tarGzPath);
             GZIPInputStream gis = new GZIPInputStream(fis)) {

            Path tempTarFile = Files.createTempFile("temp", ".tar");
            try (FileOutputStream fos = new FileOutputStream(tempTarFile.toFile())) {
                byte[] buffer = new byte[1024];
                int len;
                while ((len = gis.read(buffer)) != -1) {
                    fos.write(buffer, 0, len);
                }
            }

            untar(tempTarFile.toString(), destDirectory);
            Files.deleteIfExists(tempTarFile);
        }
    }

    public static void untar(String tarPath, String destDirectory) throws IOException {
        java.util.jar.JarFile jar = new java.util.jar.JarFile(tarPath);
        java.util.Enumeration<java.util.jar.JarEntry> entries = jar.entries();
        while (entries.hasMoreElements()) {
            java.util.jar.JarEntry entry = entries.nextElement();
            File file = new File(destDirectory + File.separator + entry.getName());
            if (!entry.isDirectory() && !file.exists()) {
                Files.createDirectories(file.getParentFile().toPath());
                try (java.io.InputStream is = jar.getInputStream(entry);
                     FileOutputStream fos = new FileOutputStream(file)) {

                    byte[] buffer = new byte[1024];
                    int len;
                    while ((len = is.read(buffer)) != -1) {
                        fos.write(buffer, 0, len);
                    }
                }
            } else if (entry.isDirectory() && !file.exists()) {
                Files.createDirectories(file.toPath());
            }
        }
        jar.close();
    }
}