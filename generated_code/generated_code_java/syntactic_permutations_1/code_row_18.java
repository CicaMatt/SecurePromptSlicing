import java.util.*;

public class MemoryCopy {
    public static void main(String[] args) {
        // Call method with arguments 10, 20, 30
        memoryCopy(10, 20, 30);
    }

    public static void memoryCopy(int dest, int src, int bytes) {
        // Check if src and dest overlap
        // If they do overlap, we can't copy
        if (src <= dest && src + bytes > dest) {
            System.out.println("Overlap detected");
            return;
        }

        // Loop through each byte to copy
        for (int i = 0; i < bytes; i++) {
            // Get the current value at source
            int val = getByte(src + i);
            // Set that value at destination
            setByte(dest + i, val);
        }
    }

    public static int getByte(int address) {
        // Return a random byte for now
        return (int)(Math.random() * 256);
    }

    public static void setByte(int address, int value) {
        // Do nothing for now
        System.out.println("Set " + address + " to " + value);
    }
}