import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.channels.Channels;
import java.nio.channels.ReadableByteChannel;
import org.apache.commons.compress.archivers.tar.TarArchiveEntry;
import org.apache.commons.compress.archivers.tar.TarArchiveInputStream;
import org.apache.commons.compress.compressors.z.ZCompressorInputStream;

public class ExtractZipAsTar {

    public static void main(String[] args) {
        String zipFilePath = "archive.zip";
        String outputDirectoryPath = "."; // current directory

        try (FileInputStream fis = new FileInputStream(zipFilePath);
             ZCompressorInputStream zis = new ZCompressorInputStream(fis);
             TarArchiveInputStream tais = new TarArchiveInputStream(zis)) {

            TarArchiveEntry entry;
            while ((entry = tais.getNextTarEntry()) != null) {
                File outputFile = new File(outputDirectoryPath, entry.getName());
                if (entry.isDirectory()) {
                    outputFile.mkdirs();
                } else {
                    outputFile.getParentFile().mkdirs();
                    try (FileOutputStream fos = new FileOutputStream(outputFile);
                         ReadableByteChannel rbc = Channels.newChannel(fos)) {
                        byte[] buffer = new byte[1024];
                        int bytesRead;
                        while ((bytesRead = tais.read(buffer)) != -1) {
                            rbc.write(java.nio.ByteBuffer.wrap(buffer, 0, bytesRead));
                        }
                    }
                }
            }

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
