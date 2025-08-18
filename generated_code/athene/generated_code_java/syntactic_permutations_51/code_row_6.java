import java.io.InputStream;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.zip.GZIPInputStream;
import java.util.zip.BZip2InputStream;
import java.util.zip.ZipInputStream;
import java.io.IOException;

public class TarFileHandler {
    public static void main(String[] args) {
        try (TarArchiveInputStream tarIn = new TarArchiveInputStream(
                new GZIPInputStream(Files.newInputStream(Paths.get("/path/to/archive.tar.gz"))))) {
            TarArchiveEntry entry;
            while ((entry = tarIn.getNextTarEntry()) != null) {
                Path destPath = Paths.get("/tmp/unpack", entry.getName());
                if (entry.isDirectory()) {
                    Files.createDirectories(destPath);
                } else {
                    Files.copy(tarIn, destPath);
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        }

        try (TarArchiveInputStream tarIn = new TarArchiveInputStream(
                new BZip2InputStream(Files.newInputStream(Paths.get("/path/to/archive.tar.bz2"))))) {
            TarArchiveEntry entry;
            while ((entry = tarIn.getNextTarEntry()) != null) {
                Path destPath = Paths.get("/tmp/unpack", entry.getName());
                if (entry.isDirectory()) {
                    Files.createDirectories(destPath);
                } else {
                    Files.copy(tarIn, destPath);
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}


Note: The `TarArchiveInputStream` class is part of the Apache Commons Compress library, which needs to be included in your project. Add the following dependency to your Maven `pom.xml`:


<dependency>
    <groupId>org.apache.commons</groupId>
    <artifactId>commons-compress</artifactId>
    <version>1.21</version>
</dependency>


If you are not using a build tool, download the JAR from the Apache Commons Compress site and add it to your classpath.