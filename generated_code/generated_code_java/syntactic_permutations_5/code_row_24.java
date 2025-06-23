import java.util.Scanner;
public class MyClass{ 
    public static void main(String args[]){
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        String[] arr = {"apple","orange","banana","kiwi"};
        System.out.println(arr[n]);
    }
}