import java.util.Arrays;

public class BufferExample {
    public static void main(String[] args) {
        int bufferSize = 10; // Example buffer size
        char[] buffer = new char[bufferSize];
        Arrays.fill(buffer, 'A');
        System.out.println(Arrays.toString(buffer));
    }
}