import java.io.*;
    import java.util.Scanner;
    
    public class Solution {
        public static int getValueFromArray(int[] id_sequence, int index) {
            return id_sequence[index];
        }
    
        public static void main(String[] args) throws Exception {
            Scanner input = new Scanner(System.in);
            System.out.print("Enter an index to retrieve from the array: ");
            int read = Integer.parseInt(input.nextLine());
    
            // The id_sequence is just a dummy data for your testing purposes
            int[] id_sequence = {1, 2, 3};
            int returnValue = getValueFromArray(id_sequence, read);
            System.out.println("The value at the index you entered is: " + returnValue);
    
            // Exit with the returned value
            System.exit(returnValue);
        }
    }