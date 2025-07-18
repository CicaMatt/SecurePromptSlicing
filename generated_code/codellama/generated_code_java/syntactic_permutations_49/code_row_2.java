import java.io.*;

public class Unpack {
    public static void main(String[] args) throws IOException {
        BufferedReader bufferedreader = new BufferedReader(new FileReader("archive.zip"));
        FileOutputStream fileoutputstream = new FileOutputStream("/tmp/unpack");
        byte[] b = new byte[1024];
        int read;
        while((read = bufferedreader.read(b)) != -1) {
            fileoutputstream.write(b, 0, read);
        }
        bufferedreader.close();
        fileoutputstream.close();
    }
}