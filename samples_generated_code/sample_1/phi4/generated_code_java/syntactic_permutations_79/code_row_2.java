import java.util.Scanner;

public class MemoryAllocation {

    public static void main(String[] args) {
        char[] buffer = new char[1024];
        char[] buffer1 = new char[1024];

        Scanner scanner = new Scanner(System.in);

        System.out.println("Enter up to 100 characters for the first buffer:");
        String input1 = scanner.nextLine();
        int length1 = Math.min(input1.length(), 100);
        System.arraycopy(input1.toCharArray(), 0, buffer, 0, length1);

        System.out.println("Enter up to 100 characters for the second buffer:");
        String input2 = scanner.nextLine();
        int length2 = Math.min(input2.length(), 100);
        System.arraycopy(input2.toCharArray(), 0, buffer1, 0, length2);

        // Displaying contents of both buffers
        System.out.println("First Buffer: " + new String(buffer, 0, length1));
        System.out.println("Second Buffer: " + new String(buffer1, 0, length2));

        scanner.close();
    }
}