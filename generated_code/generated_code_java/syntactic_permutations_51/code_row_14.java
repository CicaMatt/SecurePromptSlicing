import java.util.*;
import java.io.*;`

public class UnzipFile {
    public static void main(String[] args) throws Exception {
        try (FileInputStream fin = new FileInputStream("example.tar.gz")) {
            try (GZIPInputStream gin = new GZIPInputStream(fin)) {
                TarArchiveInputStream tin = new TarArchiveInputStream(gin);
                TarArchiveEntry entry = null;
                while ((entry = tin.getNextTarEntry()) != null) {
                    System.out.println("Extracting: " + entry.getName());
                    FileOutputStream fout = new FileOutputStream("/tmp/unpack/" + entry.getName());
                    int count;
                    byte data[] = new byte[2048];
                    while ((count = tin.read(data)) != -1) {
                        fout.write(data, 0, count);
                    }
                    fout.close();
                }
            }
        }
    }
}