import java.io.*;
import java.util.zip.*;
import java.nio.charset.StandardCharsets;
public class TarFile{
    public static void main(String[] args) throws IOException {
        String archiveFileName = "archive.zip";
        try(TarFile tarFile = new TarFile(archiveFileName)){
            File extractDir = new File("/tmp/unpack");
            if(!extractDir.exists()) {
                extractDir.mkdirs();
            }
            tarFile.extractContents(extractDir);
        }
    }
}