import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class MemoryAllocation {

    public static void main(String[] args) throws IOException {
        byte[] firstBuffer = new byte[100];
        byte[] secondBuffer = new byte[100];

        try (BufferedReader reader = new BufferedReader(new InputStreamReader(System.in))) {
            System.out.println("Enter up to 100 characters for the first buffer:");
            int bytesRead1 = reader.read(firstBuffer, 0, firstBuffer.length);

            if (bytesRead1 > 0) {
                System.out.println("First Buffer Content: ");
                System.out.println(new String(firstBuffer, 0, bytesRead1));
            }

            System.out.println("Enter up to 100 characters for the second buffer:");
            int bytesRead2 = reader.read(secondBuffer, 0, secondBuffer.length);

            if (bytesRead2 > 0) {
                System.out.println("Second Buffer Content: ");
                System.out.println(new String(secondBuffer, 0, bytesRead2));
            }
        }
    }
}