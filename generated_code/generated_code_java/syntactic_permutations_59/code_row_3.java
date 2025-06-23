public class Buffer {

        private final int BUFFER_SIZE = 1024;
        char[] buffer = new char[BUFFER_SIZE];

        public void allocateBuffer() {
            for (int i = 0; i < BUFFER_SIZE; i++) {
                buffer[i] = 'A';
            }
        }
    }