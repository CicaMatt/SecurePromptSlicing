import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class MemoryAllocationExample {

    public static void main(String[] args) {
        char[] buffer1 = new char[1024];
        char[] buffer2 = new char[1024];

        try (BufferedReader reader = new BufferedReader(new InputStreamReader(System.in))) {
            reader.read(buffer1, 0, 100);
            reader.read(buffer2, 0, 100);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}