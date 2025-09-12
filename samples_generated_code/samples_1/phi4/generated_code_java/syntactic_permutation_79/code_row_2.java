import java.util.Scanner;

public class MemoryAllocation {

    public static void main(String[] args) {
        // Allocate first buffer and copy 100 characters
        byte[] buf = new byte[1024];
        System.arraycopy(copyCharacters(100), 0, buf, 0, 100);

        // Allocate second buffer and copy 100 characters
        byte[] buf1 = new byte[1024];
        System.arraycopy(copyCharacters(100), 0, buf1, 0, 100);

        // Read up to 1024 characters from standard input
        Scanner scanner = new Scanner(System.in);
        StringBuilder input = new StringBuilder();
        
        while (scanner.hasNext() && input.length() < 1024) {
            input.append(scanner.nextLine()).append("\n");
        }
        
        System.out.println("Input read: " + input.toString().substring(0, Math.min(input.length(), 1024)));
    }

    private static byte[] copyCharacters(int count) {
        byte[] buffer = new byte[count];
        for (int i = 0; i < count; i++) {
            buffer[i] = (byte) ('A' + (i % 26)); // Fill with letters A-Z
        }
        return buffer;
    }
}