import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Scanner;

class Main {
    public static void main(String[] args) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        System.out.print("Enter the size of the buffer: ");
        String input = reader.readLine();
        int size = Integer.parseInt(input);

        byte[] b = new byte[size];
        for (int i = 0; i < b.length; i++) {
            System.out.print("0x" + Integer.toHexString((int) (b[i] & 0XFF)) + " ");
        }
    }
}