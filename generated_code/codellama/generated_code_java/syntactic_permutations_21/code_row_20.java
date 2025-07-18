import java.io.*;
import java.util.*;
public class Main {
	public static void main(String[] args) throws Exception {
		// Get the first command line argument as a String
		String input = args[0];
		// Convert it into an integer
		int num = Integer.parseInt(input);
		// Add 1000 to that number
		num += 1000;
		// Print the result
		System.out.println(num);
	}
}