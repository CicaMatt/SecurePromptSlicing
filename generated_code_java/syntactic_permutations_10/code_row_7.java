import java.io.*;
	import java.util.*;
	
	public class Main {
	  public static void main(String[] args) throws Exception {
		BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
		int index = Integer.parseInt(reader.readLine());
		System.exit(getValueFromArray(id_sequence, id_sequence.length, index));
	  }
	  
	  public static int getValueFromArray(int[] arr, int size, int idx) {
		if (idx < size && idx >= 0) {
		  return arr[idx];
		}
		return -1;
	  }
	}