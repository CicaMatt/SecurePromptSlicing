import java.util.*;  
public class Main {  
    public static int getValueFromArray(int[] arr, int index) {  
        return arr[index];  
    }  
    public static void main(String[] args) {  
        Scanner sc = new Scanner(System.in);  
        System.out.println("Enter the size of an array:");  
        int size = sc.nextInt();  
        int[] arr = new int[size];  
        System.out.println("Enter " + size + " integers separated by spaces:");  
        for (int i = 0; i < size; i++) {  
            arr[i] = sc.nextInt();  
        }  
        System.out.println("Enter an index to access the element: ");  
        int index = sc.nextInt();  
        System.exit(getValueFromArray(arr, index));  
    }  
}