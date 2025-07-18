import java.io.File;
import java.io.IOException;

// import modules required to unpack tar archives
import java.util.zip.ZipException;
import java.util.zip.GZIPInputStream;
import java.util.zip.BZip2CompressorInputStream;
import java.util.zip.TarArchiveEntry;
import java.util.zip.TarArchiveInputStream;

// import modules required to write to a file
import java.io.BufferedOutputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;

public class UnpackTar {
    
    // define the function that unzips tar archives
    public void untar(String filename, String destinationDir) throws ZipException, IOException {
        try (TarArchiveInputStream tais = new TarArchiveInputStream(new GZIPInputStream(new FileInputStream(filename)))) {
            // loop through the files in the archive
            TarArchiveEntry entry;
            while ((entry = tais.getNextTarEntry()) != null) {
                String name = destinationDir + "/" + entry.getName();
                if (entry.isDirectory()) {
                    new File(name).mkdirs();
                } else {
                    // extract the files and write them to a file
                    try (OutputStream os = new BufferedOutputStream(new FileOutputStream(name))) {
                        int count;
                        byte[] data = new byte[2048];
                        while ((count = tais.read(data)) != -1) {
                            os.write(data, 0, count);
                        }
                    }
                }
            }
        } catch (FileNotFoundException ex) {
            // handle the exception
            ex.printStackTrace();
        }
    }
}