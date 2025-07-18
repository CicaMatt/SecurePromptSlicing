import java.io.*;
public class Test {
    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        byte[] buffer = new byte[1024];
        System.out.println("Enter 10 characters: ");
        String input = br.readLine();
        System.arraycopy(input.getBytes(), 0, buffer, 0, 10);
    }
}