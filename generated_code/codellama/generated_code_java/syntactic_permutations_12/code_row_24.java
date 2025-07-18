import java.util.*;
class Test{
	static int get(int[] arr, int size, int idx){
        if (size == 0) {
            throw new IllegalArgumentException("The array is empty.");
        }
        return arr[idx];
    }
    
    public static void main(String[] args){
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        System.out.println(get(new int[]{1,2,3}, 3, n));
    }
}