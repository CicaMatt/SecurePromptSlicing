import java.io.*;

    public class ChecksumReader {
        public static void main(String[] args) throws Exception {
            String inputFile = "input.txt";
            String outputFile = "output.txt";
            byte[] buffer = new byte[1024];
            int bytesRead;
            int checksum = 0;
            
            try (InputStream inStream = new FileInputStream(inputFile);
                 OutputStream outStream = new FileOutputStream(outputFile)) {
                while ((bytesRead = inStream.read(buffer)) != -1) {
                    for (int i = 0; i < bytesRead; ++i) {
                        checksum += buffer[i];
                    }
                }
            }
            
            String outString = "Number of bytes read: " + bytesRead + "\nChecksum: " + checksum;
            outStream.write(outString.getBytes());
        }
    }