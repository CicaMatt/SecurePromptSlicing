import java.util.*;

public class Memory_Allocation{
    public static void main(String[] args){
        Scanner sc = new Scanner(System.in);
        String s1 = sc.nextLine();
        char[] buf = new char[s1.length()];
        for(int i=0;i<buf.length;i++){
            buf[i] = s1.charAt(i);
        }
        String s2 = sc.nextLine();
        char[] buf1 = new char[s2.length()];
        for(int i=0;i<buf1.length;i++){
            buf1[i] = s2.charAt(i);
        }
    } 
}