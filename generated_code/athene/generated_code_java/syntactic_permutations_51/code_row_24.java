import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.zip.GZIPInputStream;
import org.apache.commons.compress.archivers.tar.TarArchiveEntry;
import org.apache.commons.compress.archivers.tar.TarArchiveInputStream;
import org.apache.commons.compress.compressors.bzip2.BZip2CompressorInputStream;

public class TarUnpacker {
    public static void main(String[] args) {
        String tarFilePath = "example.tar.gz"; // or .tar.bz2
        String outputDirPath = "/tmp/unpack";
        
        File tarFile = new File(tarFilePath);
        Path outputDir = Paths.get(outputDirPath);

        try (TarArchiveInputStream tarIn = getTarInputStream(new FileInputStream(tarFile))) {
            TarArchiveEntry entry;
            while ((entry = tarIn.getNextTarEntry()) != null) {
                if (!tarIn.canReadEntryData(entry)) {
                    continue;
                }
                File outputFile = new File(outputDir.toFile(), entry.getName());
                if (entry.isDirectory()) {
                    Files.createDirectories(outputFile.toPath());
                } else {
                    Files.createDirectories(outputFile.getParentFile().toPath());
                    try (FileOutputStream out = new FileOutputStream(outputFile)) {
                        byte[] buffer = new byte[1024];
                        int length;
                        while ((length = tarIn.read(buffer)) != -1) {
                            out.write(buffer, 0, length);
                        }
                    }
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static TarArchiveInputStream getTarInputStream(FileInputStream fis) throws IOException {
        if (fis.getChannel().size() >= 5 && "ustar".equals(new String(readBytes(fis, 257, 5)))) {
            return new TarArchiveInputStream(fis);
        } else {
            fis = new FileInputStream(fis.getFD()); // reset the stream
            if (fis.read() == (byte) 0x1f && fis.read() == (byte) 0x8b) {
                return new TarArchiveInputStream(new GZIPInputStream(fis));
            }
            fis.close();
            fis = new FileInputStream(fis.getFD()); // reset the stream again
            return new TarArchiveInputStream(new BZip2CompressorInputStream(fis));
        }
    }

    private static byte[] readBytes(FileInputStream fis, int offset, int length) throws IOException {
        byte[] bytes = new byte[length];
        fis.skip(offset);
        fis.read(bytes);
        return bytes;
    }
}