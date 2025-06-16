import java.util.Arrays;

    public class MemoryChunk {
        private static final int BYTES_PER_INT = 4;

        private byte[] memory;

        public MemoryChunk(int size) {
            this.memory = new byte[size];
        }

        public void setValueAt(int index, int value) {
            // note: assumes that the JVM is using big-endian byte ordering
            memory[index] = (byte)(value >> 24);
            memory[index + 1] = (byte)(value >> 16);
            memory[index + 2] = (byte)(value >> 8);
            memory[index + 3] = (byte)value;
        }

        public int getValueAt(int index) {
            // note: assumes that the JVM is using big-endian byte ordering
            return ((memory[index] & 0xff) << 24)
                 | ((memory[index + 1] & 0xff) << 16)
                 | ((memory[index + 2] & 0xff) << 8)
                 | (memory[index + 3] & 0xff);
        }

        public void copyFrom(MemoryChunk other, int index) {
            System.arraycopy(other.memory, 0, this.memory, index, Math.min(this.memory.length - index, other.memory.length));
        }

        @Override
        public String toString() {
            return Arrays.toString(Arrays.stream(memory).mapToInt(b -> b & 0xff).toArray());
        }
    }

    public class MemoryCopyApp {
        public static void main(String[] args) {
            int size1 = 8;
            int size2 = 16;
            MemoryChunk chunk1 = new MemoryChunk(size1);
            MemoryChunk chunk2 = new MemoryChunk(size2);

            for (int i = 0; i < size1 / BYTES_PER_INT; i++) {
                int value = i * 37;
                chunk1.setValueAt(i, value);
                System.out.println("Wrote " + value + " to chunk 1 at index " + i);
            }

            for (int i = 0; i < size2 / BYTES_PER_INT; i++) {
                int value = -i * 43;
                chunk2.setValueAt(i, value);
                System.out.println("Wrote " + value + " to chunk 2 at index " + i);
            }

            System.out.println("\nContents of chunk 1 before copy:");
            System.out.println(chunk1);

            int index = size2 / BYTES_PER_INT - size1 / BYTES_PER_INT;
            System.out.println("\nCopying contents of chunk 1 to chunk 2 at index " + index);
            chunk2.copyFrom(chunk1, index * BYTES_PER_INT);

            System.out.println("Contents of chunk 2 after copy:");
            System.out.println(chunk2);
        }
    }