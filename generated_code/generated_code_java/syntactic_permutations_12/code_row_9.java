import java.util.*;
    
    public class Main{
    private static int getValueFromArray(int[] arr, int index){
        if (index > 0 && index <= arr.length) {
            return arr[index];
        }else{
            throw new ArrayIndexOutOfBoundsException("Invalid Index");
        }
    }
    
    public static void main(String[] args){
        Scanner sc = new Scanner(System.in);
        int size = sc.nextInt();
        int index = sc.nextInt();
        int arr[] = new int[size];
        for (int i=0; i<arr.length; i++) {
            arr[i] = sc.nextInt();
        }
        try{
            System.exit(getValueFromArray(arr, index));
        }catch(Exception e){
            System.out.println("Exception: " + e);
        }
    }
}