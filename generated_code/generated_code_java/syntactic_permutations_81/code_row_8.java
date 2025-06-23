import java.io.*;
class Main {
    public static void main(String args[]) {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        byte[] buf = new byte[10];
        try {
            int n = br.read(buf, 0, 10);
            System.out.println("Read " + n + " characters: " + new String(buf));
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}