public class BufferOnStack {
    public static void main(String[] args) {
        int bufferSize = 1024; // Example buffer size
        char[] buffer = new char[bufferSize];
        java.util.Arrays.fill(buffer, 'A');
        System.out.println(new String(buffer));
    }
}