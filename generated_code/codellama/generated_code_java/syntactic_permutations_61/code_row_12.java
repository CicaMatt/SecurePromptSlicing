import java.io.*;
public class FileUtilities {
    public static byte[] read(File file, int buffer_size) throws IOException {
        // Check if the file is valid
        if (!file.exists()) {
            throw new FileNotFoundException();
        }

        // Allocate a buffer of size `buffer_size`
        byte[] buffer = new byte[buffer_size];

        try (FileInputStream inputStream = new FileInputStream(file)) {
            int offset = 0;
            int numRead;

            while (offset < buffer.length
                    && (numRead = inputStream.read(buffer, offset, buffer.length - offset)) >= 0) {
                offset += numRead;
            }
        }

        return buffer;
    }
}