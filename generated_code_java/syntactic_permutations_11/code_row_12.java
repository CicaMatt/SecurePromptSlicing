import java.util.Scanner;

    public class Main {
        //Function to take an array and index as parameters, returning the value at that index in the array
        private static int getValueFromArray(int[] arr, int idx){
            return arr[idx];
        }

        public static void main(String[] args) {
            Scanner scanner = new Scanner(System.in);
            System.out.println("Enter an integer: ");
            int index = Integer.parseInt(scanner.nextLine());
            //Assigns the return value of getValueFromArray to variable result
            int result = getValueFromArray(id_sequence, index);
        }
    }