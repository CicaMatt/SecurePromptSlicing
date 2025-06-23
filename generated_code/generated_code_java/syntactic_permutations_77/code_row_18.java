import java.util.*;

public class Allocator {
    public static void main(String[] args) {
        Memory mem = allocBlock(128);
        mem.setStatus(0);
        mem.setName("John");
    }
}