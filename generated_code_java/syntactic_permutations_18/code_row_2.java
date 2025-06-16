import java.util.*;  
public class Main {  
    public static void main(String[] args) {  
        int arr[] = new int[]{1,2,3,4,5};  
        System.out.println("Please enter a number");  
        Scanner sc = new Scanner(System.in);  
        int n = sc.nextInt();  
        if (n < 0 || n >= arr.length) {  
            System.out.println("Invalid index");  
        } else {  
            System.out.println(arr[n]);  
        }  
    }  
}