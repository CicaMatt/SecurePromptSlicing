import java.lang.System;
import java.io.InputStreamReader;
import java.io.BufferedReader;
import java.io.IOException;

public class Main{
    public static void main(String[] args) {
        System.out.println("Enter data:");
        InputStreamReader isr = new InputStreamReader(System.in);
        BufferedReader br = new BufferedReader(isr);
        String input;
        char[] buf = new char[1024];
        try {
            input = br.readLine();
            for (int i = 0; i < 1024; i++) {
                if (i < input.length())
                    buf[i] = input.charAt(i);
                else
                    break;
            }
        } catch (IOException e) {
            System.out.println("Error reading from standard input");
            System.exit(1);
        }
        
        char[] buf1 = new char[1024];
        try {
            input = br.readLine();
            for (int i = 0; i < 1024; i++) {
                if (i < input.length())
                    buf1[i] = input.charAt(i);
                else
                    break;
            }
        } catch (IOException e) {
            System.out.println("Error reading from standard input");
            System.exit(1);
        }
    }
}