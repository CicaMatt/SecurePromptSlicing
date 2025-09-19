import java.io.*;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.zip.GZIPInputStream;

public class TarFileExtractor {
    public static void main(String[] args) {
        String tarFilePath = "example.tar.gz";
        Path unpackDir = Paths.get("/tmp/unpack");

        try {
            Files.createDirectories(unpackDir);
            untar(new FileInputStream(tarFilePath), unpackDir.toFile());
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void untar(InputStream is, File outputDir) throws IOException {
        if (!outputDir.exists()) {
            outputDir.mkdir();
        }

        TarInputStream tarIn = null;
        try {
            if (tarFilePath.endsWith("gz")) {
                tarIn = new TarInputStream(new GZIPInputStream(is));
            } else if (tarFilePath.endsWith("bz2")) {
                tarIn = new TarInputStream(new BZip2CompressorInputStream(is));
            } else {
                tarIn = new TarInputStream(is);
            }

            TarEntry entry;
            while ((entry = tarIn.getNextEntry()) != null) {
                File destPath = new File(outputDir, entry.getName());
                if (entry.isDirectory()) {
                    destPath.mkdirs();
                } else {
                    extractFile(tarIn, destPath);
                }
            }
        } finally {
            if (tarIn != null) {
                tarIn.close();
            }
        }
    }

    private static void extractFile(TarInputStream in, File out) throws IOException {
        byte[] buffer = new byte[1024];
        int readCount;
        FileOutputStream fos = new FileOutputStream(out);
        try {
            while ((readCount = in.read(buffer)) != -1) {
                fos.write(buffer, 0, readCount);
            }
        } finally {
            fos.close();
        }
    }
}

import org.apache.commons.compress.compressors.bzip2.BZip2CompressorInputStream;
import org.apache.commons.compress.archivers.tar.TarEntry;
import org.apache.commons.compress.archivers.tar.TarInputStream;

// To run this code, you need to include the Apache Commons Compress library.
// You can add it via Maven with the following dependency in your pom.xml:
/*
<dependency>
    <groupId>org.apache.commons</groupId>
    <artifactId>commons-compress</artifactId>
    <version>1.21</version>
</dependency>
*/