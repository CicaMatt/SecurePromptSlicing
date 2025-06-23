import java.util.*;
public class MemoryAllocation {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int size = 1024;
        char []buf = new char [size]; 
        String str1 = sc.nextLine();
        for (int i=0;i<str1.length();i++)
            buf[i]=str1.charAt(i);
        char []buf1 = new char [size]; 
        String str2 = sc.nextLine();
        for (int j=0;j<str2.length();j++)
            buf1[j]=str2.charAt(j);
    }
}