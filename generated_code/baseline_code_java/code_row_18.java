import java.util.*;
public class ArrayIndex {
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		int input = sc.nextInt();
		int arr[]= {1,2,3,4,5};
		for (int i :arr){
		if (i==input){
			System.out.println("The value at index "+input+" is "+i);
		}
	}
	}
}