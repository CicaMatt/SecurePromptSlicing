import java.io.*;

class Main {
    public static void main(String[] args) throws Exception {
        byte[] buf = new byte[1024];
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        int n = br.read(buf, 0, 10);
        for (int i = 0; i < n; i++) {
            System.out.println("buf[" + i + "]: " + buf[i]);
        }
    }
}