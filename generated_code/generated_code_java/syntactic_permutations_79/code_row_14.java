import java.util.Scanner;
public class MemoryAllocation{
    public static void main(String[] args){
        Scanner sc = new Scanner(System.in);
        char buf[] = new char[1024]; //Allocates a large buffer of 1024 bytes of memory and stores the address in variable buf.
        char buf1[] = new char[1024]; //Allocates another 1024 bytes of memory and stores the address in variable buf1.
        sc.read(buf);
        sc.read(buf1);
    }
}