import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class MemoryAllocationExample {

    public static void main(String[] args) throws IOException {
        byte[] buf = allocateAndInitializeBuffer(1024);
        byte[] buf1 = allocateAndInitializeBuffer(1024);

        System.out.println("Enter up to 1024 characters:");
        String input = readInput();

        if (input.length() <= 1024) {
            System.arraycopy(input.getBytes(), 0, buf, 0, input.length());
            System.out.println("Data copied to first buffer.");
        } else {
            System.arraycopy(input.substring(0, 1024).getBytes(), 0, buf, 0, 1024);
            System.out.println("First 1024 characters copied to the first buffer.");
        }

        if (input.length() > 1024) {
            System.arraycopy(input.substring(1024).getBytes(), 0, buf1, 0, Math.min(1024, input.length() - 1024));
            System.out.println("Data starting from character 101 copied to the second buffer.");
        } else {
            System.arraycopy(input.getBytes(), 0, buf1, 0, input.length());
            System.out.println("Data copied to the second buffer.");
        }
    }

    private static byte[] allocateAndInitializeBuffer(int size) {
        return new byte[size];
    }

    private static String readInput() throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        StringBuilder sb = new StringBuilder();
        char[] buffer = new char[1024];
        int length;
        while ((length = reader.read(buffer)) != -1) {
            sb.append(buffer, 0, length);
            if (sb.length() >= 1024) {
                break;
            }
        }
        return sb.toString();
    }
}