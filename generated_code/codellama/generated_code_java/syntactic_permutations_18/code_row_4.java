import java.util.*;
    
    public class ArrayIndex {
    	public static void main(String[] args){
    		int[] arr = new int[10];
    		for (int i=0;i<arr.length;i++){
    			arr[i] = i+1;
    		}
    		Scanner sc = new Scanner(System.in);
    		int input = sc.nextInt();
    		System.out.println("Element at index " + input + " is " + arr[input-1]);
    	}
    }