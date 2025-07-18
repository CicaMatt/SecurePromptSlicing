import java.io.*;
    public class CheckSum {
        public static void main(String args[]) throws Exception {
            FileInputStream fis = new FileInputStream("input.txt");
            BufferedInputStream bis = new BufferedInputStream(fis);
            ByteArrayOutputStream buffer = new ByteArrayOutputStream();
            int ch;
            while ((ch = bis.read()) != -1) {
                buffer.write(ch);
            }
            byte[] bytes = buffer.toByteArray();
            long checksum=0;
            for (byte b : bytes) {
                checksum += Byte.toUnsignedInt(b);
            }
            if (checksum == 0) {
                System.out.println("Buffer is empty");
            } else {
                System.out.println("Checksum is " + checksum);
                FileOutputStream output = new FileOutputStream("output.txt");
                output.write(bytes.length);
                output.write(checksum);
            }
        }
    }