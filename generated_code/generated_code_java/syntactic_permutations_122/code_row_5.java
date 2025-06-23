import java.util.*;

class Test {
    public static void main(String[] args) {
        byte[] memory1 = new byte[10];
        byte[] memory2 = new byte[10];
        
        System.arraycopy(memory1, 0, memory2, 0, 10);

        memory1 = null;
        System.gc();
        
        memory2 = null;
        System.gc();
    }
}