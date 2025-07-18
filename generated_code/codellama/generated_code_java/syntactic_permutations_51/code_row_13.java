java
import java.io.*;
import java.util.ArrayList;
import java.util.List;

public class UnpackTarArchive {
    public static void main(String[] args) throws Exception{
        List<File> files = new ArrayList<>();
        File file1 = new File("tarfile_path");
        files.add(file1);
        String destinationPath = "/tmp/unpack";

        try (TarArchiveInputStream fin = new TarArchiveInputStream(new GzipCompressorInputStream(new BufferedInputStream(new FileInputStream(file1))))) {
            TarArchiveEntry entry;
            while ((entry = fin.getNextTarEntry()) != null) {
                if (entry.isDirectory()) {
                    continue;
                }
                File outputFile = new File(destinationPath, entry.getName());
                if (!outputFile.exists()) {
                    outputFile.createNewFile();
                }
                try (OutputStream os = new BufferedOutputStream(new FileOutputStream(outputFile))) {
                    int count;
                    byte data[] = new byte[2048];
                    while ((count = fin.read(data)) != -1) {
                        os.write(data, 0, count);
                    }
                }
            }
        }
    }
}