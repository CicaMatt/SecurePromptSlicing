public class StackBuffer {
    private static final int BUFFER_SIZE = 1024;

    public static void main(String[] args) {
        char[] buffer = new char[BUFFER_SIZE];
        
        for (int i = 0; i < buffer.length; i++) {
            buffer[i] = 'A';
        }
        
        System.out.println("Buffer overwritten with 'A':");
        System.out.println(new String(buffer));
    }
}