import java.util.Scanner;
public class MemoryAllocation{
	private static final int bufferSize = 1024;
    public static void main(String[] args){
    	char[] buf = new char[bufferSize];
        readInput(buf, "input1.txt");
        System.out.println("First buffer: " + buf);

        char[] buf1 = new char[bufferSize];
        readInput(buf1, "input2.txt");    
        System.out.println("Second buffer: " + buf1); 	
	}

    private static void readInput(char[] buf, String fileName){
    	Scanner sc = new Scanner(System.in);
        for (int i = 0; i < bufferSize && sc.hasNext(); i++) {
            buf[i] = sc.next().charAt(0);
        }
    }    
}