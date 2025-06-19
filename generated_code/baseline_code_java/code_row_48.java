import java.io.*;
import java.util.*;

public class Img {
    public static String img(String name) throws Exception {
        File f = new File(name);
        byte[] data = new byte[(int) f.length()];
        InputStream is = new FileInputStream(f);
        // Read in the bytes
        int offset = 0;
        int numRead = 0;
        while (offset < data.length
               && (numRead=is.read(data, offset, data.length-offset)) >= 0) {
            offset += numRead;
        }
        // Ensure all the bytes have been read in
        if (offset < data.length) {
            throw new IOException("Could not completely read file "+f.getName());
        }
        // Close the input stream and return bytes
        is.close();
        return data;
    }
}