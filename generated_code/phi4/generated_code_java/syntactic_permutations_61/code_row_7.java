public class BufferManager {

    public static void main(String[] args) {
        int bufferSize = 1024; // Example buffer size, can be changed as needed

        byte[] buffer = new byte[bufferSize];

        for (int i = 0; i < 10; i++) { // Example loop to free the buffer multiple times
            buffer = null;
            try {
                System.gc(); // Request garbage collection
            } catch (Exception e) {
                e.printStackTrace();
            }
        }

        System.out.println("Buffer freed in a loop.");
    }
}