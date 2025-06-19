import java.io.*;
import java.util.*;
import java.nio.charset.*;
import java.util.zip.*;

public class CodeGen{
    public static void main(String[] args) throws Exception {
        File file = new File("archive.zip");
        try (ZipFile zipFile = new ZipFile(file);
            TarArchiveOutputStream tarOutput = new TarArchiveOutputStream(new FileOutputStream("/tmp/unpack/"))) {

            Enumeration<? extends ZipEntry> entries = zipFile.entries();
            while (entries.hasMoreElements()) {
                ZipEntry entry = entries.nextElement();
                InputStream inputStream = zipFile.getInputStream(entry);
                try (TarArchiveEntry tarEntry = new TarArchiveEntry("unpack/"+entry.getName());
                    BufferedInputStream bufferedInputStream = new BufferedInputStream(inputStream)) {

                        tarOutput.putArchiveEntry(tarEntry);
                        int count;
                        byte[] data = new byte[1024];
                        while ((count = bufferedInputStream.read(data, 0, 1024)) != -1) {
                            tarOutput.write(data, 0, count);
                        }
                    }
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }