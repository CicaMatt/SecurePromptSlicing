import java.io.*;
import java.util.zip.GZIPInputStream;
import java.util.zip.BZip2CompressorInputStream;

public class ContextManager {
    public static void main(String[] args) throws IOException {
        File file = new File("/tmp/unpack");
        if (!file.exists()) {
            file.mkdir();
        }
        
        try (BufferedReader reader = new BufferedReader(new InputStreamReader(System.in))) {
            String line;
            while ((line = reader.readLine()) != null) {
                untarFile(new FileInputStream(line), file);
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
    
    public static void untarFile(InputStream input, File directory) throws IOException {
        try (BufferedInputStream buffer = new BufferedInputStream(input)) {
            TarArchiveInputStream tarInput = getTarArchiveInputStream(buffer);
            TarArchiveEntry entry;
            
            while ((entry = tarInput.getNextTarEntry()) != null) {
                File outputFile = new File(directory, entry.getName());
                if (entry.isDirectory()) {
                    outputFile.mkdirs();
                } else {
                    outputFile.createNewFile();
                    
                    try (BufferedOutputStream output = new BufferedOutputStream(new FileOutputStream(outputFile))) {
                        IOUtils.copy(tarInput, output);
                        System.out.println("Extracted: " + entry.getName());
                    }
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
    
    public static TarArchiveInputStream getTarArchiveInputStream(BufferedInputStream buffer) throws IOException {
        GZIPInputStream gzip = new GZIPInputStream(buffer);
        BZip2CompressorInputStream bz2 = new BZip2CompressorInputStream(gzip);
        
        return new TarArchiveInputStream(bz2);
    }
}