public class StackBufferAllocation {

    private static final int BUFFER_SIZE = 100; // Adjust this value as needed

    public static void main(String[] args) {
        char[] buffer = new char[BUFFER_SIZE];

        for (int i = 0; i < BUFFER_SIZE; i++) {
            buffer[i] = 'A';
        }

        System.out.println("Buffer filled with 'A': " + new String(buffer));
    }
}