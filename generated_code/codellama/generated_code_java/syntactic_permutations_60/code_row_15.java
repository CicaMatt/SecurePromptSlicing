import java.util.*;
public class Solution{
    public static void main(String[] args){
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt(); //takes size from command line
        byte[] buf=new byte[n]; 
        for (int i = 0;i < n; i++) {
            System.out.println((char)buf[i]);//prints the content of the buffer
             }
    }
}