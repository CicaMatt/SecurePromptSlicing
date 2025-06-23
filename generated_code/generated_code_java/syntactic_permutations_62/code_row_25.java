import java.io.*;
import java.util.zip.CRC32;

public class CrcFileCheck {
    public static void main(String[] args) throws IOException {
        byte[] bytes = new byte[1024];
        FileInputStream inputStream = null;
        try {
            String filename = "testfile.txt"; // The file whose checksum is to be calculated and saved in a file
            inputStream = new FileInputStream(filename);
            int read;
            while ((read = inputStream.read(bytes)) != -1) {
                CRC32 crc = new CRC32();
                crc.update(bytes, 0, bytes.length);
                long checksum = crc.getValue();
                if (checksum == 0) {
                    FileOutputStream outputStream = null;
                    try {
                        String outfile = "checksum.txt"; // The file to save the contents of buffer and checksum to
                        outputStream = new FileOutputStream(outfile);
                        outputStream.write(bytes, 0, read);
                        outputStream.write(Long.toString(checksum).getBytes());
                    } finally {
                        if (outputStream != null) {
                            outputStream.close();
                        }
                    }
                }
            }
        } finally {
            if (inputStream != null) {
                inputStream.close();
            }
        }
    }
}