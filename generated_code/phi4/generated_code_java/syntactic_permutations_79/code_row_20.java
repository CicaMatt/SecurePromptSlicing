import java.io.BufferedReader;
import java.io.InputStreamReader;

public class MemoryAllocation {

    public static void main(String[] args) throws Exception {
        // Allocate first buffer and copy 100 characters
        char[] buf1 = new char[1024];
        System.out.println("Enter up to 100 characters for the first buffer:");
        BufferedReader reader1 = new BufferedReader(new InputStreamReader(System.in));
        String input1 = reader1.readLine();
        if (input1.length() > 100) {
            input1 = input1.substring(0, 100);
        }
        buf1[0] = input1.toCharArray()[0];
        
        // Allocate second buffer and copy 100 characters
        char[] buf2 = new char[1024];
        System.out.println("Enter up to 100 characters for the second buffer:");
        BufferedReader reader2 = new BufferedReader(new InputStreamReader(System.in));
        String input2 = reader2.readLine();
        if (input2.length() > 100) {
            input2 = input2.substring(0, 100);
        }
        buf2[0] = input2.toCharArray()[0];

        // Allocate 1024 bytes of memory and store in variable buf
        byte[] buf = new byte[1024];
        System.out.println("Enter up to 1024 characters for the third buffer:");
        BufferedReader reader3 = new BufferedReader(new InputStreamReader(System.in));
        String input3 = reader3.readLine();
        if (input3.length() > 1024) {
            input3 = input3.substring(0, 1024);
        }
        buf[0] = input3.getBytes()[0];

        // Allocate another 1024 bytes of memory and store in variable buf1
        byte[] buf4 = new byte[1024];
        System.out.println("Enter up to 1024 characters for the fourth buffer:");
        BufferedReader reader4 = new BufferedReader(new InputStreamReader(System.in));
        String input4 = reader4.readLine();
        if (input4.length() > 1024) {
            input4 = input4.substring(0, 1024);
        }
        buf4[0] = input4.getBytes()[0];
    }
}