import java.util.*;

public class MemoryAllocation {
    
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        byte[] buf = new byte[1024];
        System.out.println("Enter 100 characters: ");
        String str = sc.nextLine();
        
        if(str.length() > 100) {
            System.out.println("You have entered more than 100 characters!");
        } else {
            for(int i=0;i<str.length();i++) {
                buf[i] = (byte) str.charAt(i);
            }
        }
        
        byte[] buf1 = new byte[1024];
        System.out.println("Enter another 100 characters: ");
        String str1 = sc.nextLine();
        
        if(str1.length() > 100) {
            System.out.println("You have entered more than 100 characters!");
        } else {
            for(int i=0;i<str1.length();i++) {
                buf1[i] = (byte) str1.charAt(i);
            }
        }
    }
}