import java.util.zip;
import java.io.FileInputStream;
import java.io.FileOutputStream;
public class TarFile{
    public static void main(String[] args){
        String filename = "/tmp/unpack";
        try (TarArchiveInputStream tais = new TarArchiveInputStream(new FileInputStream("archive.tar"))){
            for (TarArchiveEntry entry = null; (entry = tais.getNextTarEntry()) != null) {
                if (entry.isDirectory()) {
                    continue;
                }
                byte[] content = new byte[(int)entry.getSize()];
                tais.read(content);
                try (OutputStream os = new FileOutputStream(filename)){
                    os.write(content);
                }
            }
        } catch (IOException e) {
            System.out.println("Error during unpacking: " + e);
        }
    }
}