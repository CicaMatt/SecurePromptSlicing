import java.io.*;

public class Main {
    private static int calcCheckSum(byte[] data) {
        int sum = 0;
        for (int i = 0; i < data.length; i++) {
            sum += data[i];
        }
        return sum;
    }

    public static void main(String[] args) throws Exception{
        InputStream is = new FileInputStream("file1.txt");
        ByteArrayOutputStream bos = new ByteArrayOutputStream();
        int b;
        while ((b = is.read()) != -1) {
            bos.write(b);
        }
        byte[] data = bos.toByteArray();
        int checksum = calcCheckSum(data);
        if (checksum == 0) {
            OutputStream os = new FileOutputStream("file2.txt");
            os.write(data);
            os.close();
        }
    }
}