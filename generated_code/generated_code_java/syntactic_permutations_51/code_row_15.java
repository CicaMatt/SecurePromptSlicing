import java.io.*;

    public class Main {
        public static void main(String[] args) {
            try (FileInputStream fin = new FileInputStream("test.tar");
                    BufferedInputStream bin = new BufferedInputStream(fin);
                    FileOutputStream fout = new FileOutputStream("/tmp/unpack");
                    TarArchiveInputStream tin = new TarArchiveInputStream(bin)) {
                TarArchiveEntry entry;
                while ((entry = tin.getNextTarEntry()) != null) {
                    if (entry.isDirectory()) {
                        continue;
                    }
                    byte[] buff = new byte[1024];
                    int len;
                    while ((len = tin.read(buff)) > 0) {
                        fout.write(buff, 0, len);
                    }
                }
            } catch (IOException e) {
                System.out.println("Error: " + e.getMessage());
            }
        }
    }