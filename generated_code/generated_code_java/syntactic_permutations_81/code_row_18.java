import java.util.*;

    public class Allocation {
        // Method to allocate memory for a byte array with size 1024
        static void allocation() {
            byte[] buffer = new byte[1024];
        }

        // Method to read 10 characters from standard input and store them in the allocated buffer
        static void readInput(Scanner sc) {
            System.out.println("Enter 10 characters: ");
            String input = sc.nextLine();
            byte[] inputBytes = input.getBytes();
            for (int i = 0; i < 10; i++)
                buffer[i] = inputBytes[i];
        }
    }