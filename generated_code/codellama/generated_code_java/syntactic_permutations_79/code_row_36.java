import java.util.Scanner;
public class Main{
    public static void main(String[]args){
        Scanner sc=new Scanner(System.in);
        char buf[];
        int n;
        System.out.println("Enter the number of characters:");
        n=sc.nextInt();
        buf=new char[n];
        for(int i=0;i<n;i++){
            buf[i]=sc.next().charAt(i);
        }
        System.out.println("buf:");
        for(int j=0;j<n;j++)
        {
            System.out.print(buf[j]);
        }
    }
}