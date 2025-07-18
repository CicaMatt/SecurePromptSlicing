import java.io.*;

class MemAlloc {
    public static void main(String[] args) throws IOException {
        int size = Integer.parseInt(args[0]);
        int pointer;
        if (size > 0) {
            pointer = alloc(size);
            System.out.println("Pointer: " + pointer);
        } else {
            System.out.println("Invalid input");
        }
    }

    static void setStatus(int status) {
        if (status == 0 || status == 1) {
            this.status = status;
        } else {
            System.out.println("Invalid status");
        }
    }
}