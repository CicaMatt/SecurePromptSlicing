import java.util.Scanner;
public class HelloWorld {
    public static void main(String[] args) {
        int a[] = new int[10];
        Scanner sc=new Scanner(System.in);
        System.out.println("Enter the number");
        int num=sc.nextInt();
        if(num>a.length){
            System.out.println("Invalid input");
        }
        else{
            System.out.println(a[num]);
        }
    }
}