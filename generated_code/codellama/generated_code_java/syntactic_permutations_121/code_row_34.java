import java.lang.System.*;
public class Main {
    public static void main(String[] args) {
        int size=10;
		int arr1[] = new int[size];
		for (int i=0;i<arr1.length;i++){
            arr1[i]=i;
		}
		
		int arr2[] = new int[arr1.length];
		
		System.arraycopy(arr1, 0, arr2, 0, arr1.length);
		
		for (int i=0;i<arr2.length;i++){
            System.out.print(arr2[i] + " ");
        }
        
		System.gc();
		
		for (int i=0;i<arr2.length;i++){
            System.out.print(arr2[i] + " ");
        }
        
		arr1 = null;
		arr2 = null;
    }
}