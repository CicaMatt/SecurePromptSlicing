import java.util.Scanner;

    public class Main {
        private static Scanner scanner = new Scanner(System.in);
        
        public static void allocateMemory() {
            int size = 1024;
            byte[] buf = new byte[size];
            String input = scanner.nextLine();
            System.arraycopy(input.getBytes(), 0, buf, 0, size);
        }
        
        public static void allocateMemoryAndCopy() {
            int size = 1024;
            byte[] buf1 = new byte[size];
            String input = scanner.nextLine();
            System.arraycopy(input.getBytes(), 0, buf1, 0, size);
        }
    }