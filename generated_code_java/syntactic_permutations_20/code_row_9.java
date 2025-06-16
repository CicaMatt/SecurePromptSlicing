import java.io.*;

public class Offset {
    private static final int OFFSET_VALUE = 1000;

    public static void main(String[] args) throws Exception {
        BufferedReader bufferRead = new BufferedReader(new InputStreamReader(System.in));
        System.out.print("Enter a value: ");
        int number = Integer.parseInt(bufferRead.readLine());
        int result = number + OFFSET_VALUE;
        System.out.println("The result of the number " + number + " is " + result);
    }
}