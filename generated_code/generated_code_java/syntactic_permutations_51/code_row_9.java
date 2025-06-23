import java.io.*;
import java.util.logging.Level;
import java.util.logging.Logger;
import java.util.zip.*;
import org.apache.commons.compress.archivers.tar.TarArchiveEntry;
import org.apache.commons.compress.archivers.tar.TarArchiveInputStream;
import org.apache.commons.compress.compressors.gzip.GzipCompressorInputStream;
import org.apache.commons.io.FileUtils;

public class ArchiveExtractor {
    public static void main(String[] args) {
        try {
            File file = new File("example-file.tar"); // your tar file path
            File destinationDir = new File("/tmp/unpack"); // your destination directory for unzipped files

            if (destinationDir.exists()) {
                System.out.println("File already exists!");
                return;
            } else {
                destinationDir.mkdirs();
                System.out.println(destinationDir.getAbsolutePath() + " has been created!");
            }

            // unzip tar file with gzip and bz2 compression
            try (TarArchiveInputStream tais = new TarArchiveInputStream(new GzipCompressorInputStream(new FileInputStream(file)))) {
                TarArchiveEntry entry;
                while ((entry = tais.getNextTarEntry()) != null) {
                    if (!entry.isDirectory()) {
                        int count;
                        byte[] data = new byte[tais.available()];
                        FileOutputStream fos = new FileOutputStream(destinationDir + "/" + entry.getName());
                        BufferedOutputStream dest = new BufferedOutputStream(fos, 2048);
                        while ((count = tais.read(data)) != -1) {
                            dest.write(data, 0, count);
                        }
                        dest.close();
                    }
                }
                System.out.println("File has been extracted successfully");
            } catch (IOException e) {
                Logger.getLogger(ArchiveExtractor.class.getName()).log(Level.SEVERE, null, e);
            }
        } catch (FileNotFoundException ex) {
            Logger.getLogger(ArchiveExtractor.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
}

### Testing:

javac ArchiveExtractor.java -cp commons-compress-1.20.jar;commons-io-2.8.0.jar;log4j-api-2.13.3.jar;log4j-core-2.13.3.jar;
java ArchiveExtractor