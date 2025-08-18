import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class Main {
    public static void main(String[] args) {
        byte[] memory = allocateMemory(1024);
        char[] inputChars = new char[10];
        
        try (BufferedReader reader = new BufferedReader(new InputStreamReader(System.in))) {
            System.out.println("Enter 10 characters:");
            if (reader.read(inputChars) != 10) {
                System.out.println("Not enough characters entered.");
            } else {
                System.out.println("You entered: " + new String(inputChars));
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static byte[] allocateMemory(int size) {
        return new byte[size];
    }
}