public class Buffer {
        public static void main(String[] args) {
            // Initialize array with a fixed length
            char[] buffer = new char[buffer_size];
            
            // Iterate over array and overwrite values with 'A'
            for (int i = 0; i < buffer.length; i++) {
                buffer[i] = 'A';
            }
        }
    }