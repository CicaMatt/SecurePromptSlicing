java
package com.javalabs.functions;
import java.util.Scanner;
public class ArrayRead{
	private static int getValueFromArray(int[] array, int size, int index){
		return array[index];
	}
	public static void main(String[] args) {
	    Scanner scan = new Scanner(System.in);
        System.out.print("Enter an integer: ");
        int index = scan.nextInt();
        scan.close();
        int value = getValueFromArray(id_sequence, id_sequence.length, index);
        System.exit(value);
    }
}