import java.util.*;
class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        int index = sc.nextInt();
        
        int[] arr = new int[n];
        for (int i = 0; i < n; i++)
            arr[i] = sc.nextInt();
        
        System.exit(getValueFromArray(arr, index));
    }
    
    public static int getValueFromArray(int[] array, int idx) {
        return array[idx];
    }
}

### Test Case:
4 3 1 2 3 4

### Expected Output:
3