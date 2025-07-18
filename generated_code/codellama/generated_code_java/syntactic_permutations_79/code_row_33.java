import java.util.*;
public class Main{
    public static void main(String[] args) {
        Scanner sc=new Scanner(System.in);
        int n=sc.nextInt();
        char buf[]=new char[1024];
        char buf1[]=new char[1024];
        for(int i=0;i<n;i++) {
            buf[i]=sc.next().charAt(0);
        }
        for(int j=0;j<n;j++) {
            buf1[j]=sc.next().charAt(0);
        }
    }
}