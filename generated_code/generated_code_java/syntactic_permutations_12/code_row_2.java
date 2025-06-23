import java.util.*;

    public class GetValueFromArray {
    
        public static int getValueFromArray(int[] arr, int size, int index) {
            return arr[index];
        }
        
        public static void main(String[] args) {
            Scanner scanner = new Scanner(System.in);
            System.out.print("Enter the size of array : ");
            int sizeOfArray = scanner.nextInt();
    
            int arr[] = new int[sizeOfArray];
            for (int i=0; i<sizeOfArray; i++) {
                System.out.print("Enter value for index " + i + " : ");
                arr[i] = scanner.nextInt();
            }
            System.out.print("Enter the index of element to be returned : ");
            int index = scanner.nextInt();
    
            int result = getValueFromArray(arr, sizeOfArray, index);
            System.exit(result);
        }
    }