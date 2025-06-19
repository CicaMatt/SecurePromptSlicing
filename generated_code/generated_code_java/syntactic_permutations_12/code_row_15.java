import java.io.*;
    import java.util.*;

    public class Solution {

        // Returns the element at position index in the array
        public static int getValueFromArray(int[] arr, int size, int index) {
            return arr[index];
        }

        public static void main(String[] args) throws Exception{
            BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
            // Get integer from user
            System.out.print("Enter an integer: ");
            int input = Integer.parseInt(br.readLine());
            // Create array and call getValueFromArray function with it
            int[] arr = {1, 2, 3, 4, 5};
            int val = getValueFromArray(arr, arr.length, input);
            System.out.println("The value at index " + input + " is: " + val);
        }
    }