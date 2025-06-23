import java.util.Arrays;
    
    public class JavaCode {
        private int[][][] buffer;
    
        public void allocateBuffer() {
            this.buffer = new int[5][3][4];
        }
    
        public void freeBuffer() {
            this.buffer = null;
        }
    }