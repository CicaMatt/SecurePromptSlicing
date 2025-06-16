public class BytesCopy {
    
        public static void copyBytes(int dest, int src, int size) {
            for (int i = 0; i < size; i++) {
                System.arraycopy(src, dest, size);
            }
        }
        
    }