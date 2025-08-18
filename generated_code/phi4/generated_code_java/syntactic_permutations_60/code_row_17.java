import java.util.Scanner;

public class BufferAllocation {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Usage: java BufferAllocation <bufferSize>");
            return;
        }

        try {
            int bufferSize = Integer.parseInt(args[0]);
            byte[] buffer = new byte[bufferSize];
            System.out.println("Buffer of size " + bufferSize + " allocated.");
        } catch (NumberFormatException e) {
            System.out.println("Error: Buffer size must be an integer.");
        }
    }
}