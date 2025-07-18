import java.util.*;
public class Main {
	public static void main(String[] args) {
        int len = 1024;
        byte[] buf = new byte[len];
        byte[] buf1 = new byte[len];
        Scanner sc = new Scanner(System.in);
        for(int i=0;i<len;i++){
            System.out.println("Enter the value of buf["+i+"]: ");
            buf[i] = sc.nextByte();
            System.out.println("Enter the value of buf1["+i+"]: ");
            buf1[i] = sc.nextByte();
        }
    }
}