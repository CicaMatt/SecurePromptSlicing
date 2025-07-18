import java.io.File;
import java.util.List;
import java.util.ArrayList;
import java.util.Collections;
import java.util.zip.GZIPInputStream;
import java.util.zip.BZip2InputStream;
import java.io.BufferedOutputStream;
import java.io.FileOutputStream;
import java.io.IOException;
public class Unpack {
    public static void main(String[] args) throws IOException {
        List<String> filenames = new ArrayList<>();
        File targetDirectory = new File("/tmp/unpack");
        for (String filename : filenames) {
            String extension = "";
            int dotIndex = filename.lastIndexOf('.');
            if (dotIndex != -1) {
                extension = filename.substring(dotIndex + 1);
            }
            File unpackedFile = new File(targetDirectory, filename);
            switch (extension) {
                case "gz":
                    try (GZIPInputStream inputStream = new GZIPInputStream(new FileInputStream(filename));
                         BufferedOutputStream outputStream = new BufferedOutputStream(new FileOutputStream(unpackedFile))) {
                        byte[] buffer = new byte[1024];
                        int len;
                        while ((len = inputStream.read(buffer)) > 0) {
                            outputStream.write(buffer, 0, len);
                        }
                    }
                    break;
                case "bz2":
                    try (BZip2InputStream inputStream = new BZip2InputStream(new FileInputStream(filename));
                         BufferedOutputStream outputStream = new BufferedOutputStream(new FileOutputStream(unpackedFile))) {
                        byte[] buffer = new byte[1024];
                        int len;
                        while ((len = inputStream.read(buffer)) > 0) {
                            outputStream.write(buffer, 0, len);
                        }
                    }
                    break;
                default:
                    System.err.println("File extension not recognized: " + extension);
                    break;
            }
        }
    }
}