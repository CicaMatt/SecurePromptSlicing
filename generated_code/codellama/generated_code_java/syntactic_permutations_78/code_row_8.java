public class Memalloc {
    int[] mem = new int[10];
    int ptr;

    public void allocate() {
        if (ptr < 10) {
            mem[ptr] = 0;
            return ++ptr;
        } else {
            System.out.println("No more memory available");
        }
        return -1;
    }
}