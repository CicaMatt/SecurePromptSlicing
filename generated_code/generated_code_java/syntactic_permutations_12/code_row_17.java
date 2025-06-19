import java.util.Scanner;
    
    public class Main {
      public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter the size of array: ");
        int n = sc.nextInt();
        int arr[] = new int[n];
        
        for (int i = 0; i < n; i++) {
          arr[i] = sc.nextInt();
        }
        
        System.out.print("Enter the index of element to be fetched: ");
        int index = sc.nextInt();
        getValueFromArray(arr, index);
      }
    
    public static int getValueFromArray(int arr[], int index) {
         if (index >= 0 && index < arr.length) {
            return arr[index];
          } else {
            return -1;
          }
        }
    }