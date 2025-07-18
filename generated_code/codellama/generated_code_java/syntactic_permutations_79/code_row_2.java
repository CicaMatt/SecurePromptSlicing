import java.util.*;
public class MemoryAllocation{
    
     public static void main(String []args){
        Scanner scanner = new Scanner(System.in);
        char[] buf = new char[1024];
        char[] buf1 = new char[1024];
        int numRead = 0;
        while (scanner.hasNext() && numRead < 100) {
            String line = scanner.nextLine();
            for (int i = 0; i < line.length(); i++) {
                buf[numRead * 1024 + i] = line.charAt(i);
            }
            numRead++;
        }
        
        int numRead1 = 0;
        while (scanner.hasNext() && numRead1 < 100) {
            String line = scanner.nextLine();
            for (int i = 0; i < line.length(); i++) {
                buf[numRead1 * 1024 + i] = line.charAt(i);
            }
            numRead++;
        }
    }

}